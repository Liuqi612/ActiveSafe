#include "tap_adapter/include/planning_snapshot.h"

#include <cassert>

namespace {

using tap::planning_adapter::PlanningInputKind;
using tap::planning_adapter::PlanningSnapshotAssembler;
using tap::planning_adapter::SnapshotFailureReason;
using tap::planning_adapter::SnapshotPolicy;
using tap::planning_adapter::TimestampNs;

constexpr TimestampNs kFrame = 10ULL * 1000ULL * 1000ULL * 1000ULL;

void AddMandatorySamples(PlanningSnapshotAssembler *assembler,
                         TimestampNs timestamp) {
    assert(assembler->Update(PlanningInputKind::kEgoState, timestamp));
    assert(assembler->Update(PlanningInputKind::kRoadStructure, timestamp));
    assert(assembler->Update(PlanningInputKind::kObjects, timestamp));
    assert(assembler->Update(PlanningInputKind::kPrediction, timestamp));
}

void TestClosedSnapshot() {
    PlanningSnapshotAssembler assembler;
    AddMandatorySamples(&assembler, kFrame);
    const auto result = assembler.Build(kFrame);
    assert(result.ok);
    assert(result.snapshot.Sample(PlanningInputKind::kEgoState).usable);
    assert(result.snapshot.Sample(PlanningInputKind::kPrediction).usable);
}

void TestMissingFutureAndStaleInputs() {
    PlanningSnapshotAssembler missing;
    assert(missing.Update(PlanningInputKind::kEgoState, kFrame));
    auto result = missing.Build(kFrame);
    assert(!result.ok);
    assert(result.failure == SnapshotFailureReason::kMissingSample);
    assert(result.input_kind == PlanningInputKind::kRoadStructure);

    PlanningSnapshotAssembler future;
    AddMandatorySamples(&future, kFrame + 1);
    result = future.Build(kFrame);
    assert(!result.ok);
    assert(result.failure == SnapshotFailureReason::kFutureSample);

    PlanningSnapshotAssembler stale;
    AddMandatorySamples(&stale, kFrame - 301ULL * 1000ULL * 1000ULL);
    result = stale.Build(kFrame);
    assert(!result.ok);
    assert(result.failure == SnapshotFailureReason::kStaleSample);
}

void TestMonotonicUpdatesAndExplicitEmptyObjects() {
    PlanningSnapshotAssembler assembler;
    assert(assembler.Update(PlanningInputKind::kEgoState, kFrame));
    assert(!assembler.Update(PlanningInputKind::kEgoState, kFrame - 1));
    assert(assembler.Latest(PlanningInputKind::kEgoState).source_timestamp_ns ==
           kFrame);

    assert(assembler.Update(PlanningInputKind::kRoadStructure, kFrame));
    assert(assembler.Update(PlanningInputKind::kObjects, kFrame, true, true));
    assert(assembler.Update(PlanningInputKind::kPrediction, kFrame));
    const auto result = assembler.Build(kFrame);
    assert(result.ok);
    assert(
        result.snapshot.Sample(PlanningInputKind::kObjects).explicitly_empty);
}

void TestSelectsHistoryBeforePlanningFrame() {
    PlanningSnapshotAssembler assembler;
    AddMandatorySamples(&assembler, kFrame - 10);
    assert(assembler.Update(PlanningInputKind::kEgoState, kFrame + 10));
    assert(assembler.Update(PlanningInputKind::kRoadStructure, kFrame + 10));
    assert(assembler.Update(PlanningInputKind::kObjects, kFrame + 10));
    assert(assembler.Update(PlanningInputKind::kPrediction, kFrame + 10));

    const auto result = assembler.Build(kFrame);
    assert(result.ok);
    assert(result.snapshot.Sample(PlanningInputKind::kEgoState)
               .source_timestamp_ns == kFrame - 10);
    assert(assembler.Latest(PlanningInputKind::kEgoState).source_timestamp_ns ==
           kFrame + 10);
}

void TestExplicitObjectOnlyFallback() {
    SnapshotPolicy policy;
    policy.allow_object_only_fallback = true;
    PlanningSnapshotAssembler assembler(policy);
    assert(assembler.Update(PlanningInputKind::kEgoState, kFrame));
    assert(assembler.Update(PlanningInputKind::kRoadStructure, kFrame));
    assert(assembler.Update(PlanningInputKind::kObjects, kFrame));
    const auto result = assembler.Build(kFrame);
    assert(result.ok);
    assert(result.snapshot.object_only_fallback);
    assert(!result.snapshot.Sample(PlanningInputKind::kPrediction).usable);
}

void TestOptionalInputsAreNotMandatory() {
    PlanningSnapshotAssembler assembler;
    AddMandatorySamples(&assembler, kFrame);
    assert(assembler.Update(PlanningInputKind::kOccupancy,
                            kFrame - 301ULL * 1000ULL * 1000ULL));
    const auto result = assembler.Build(kFrame);
    assert(result.ok);
    assert(!result.snapshot.Sample(PlanningInputKind::kOccupancy).usable);
}

}  // namespace

int main() {
    TestClosedSnapshot();
    TestMissingFutureAndStaleInputs();
    TestMonotonicUpdatesAndExplicitEmptyObjects();
    TestSelectsHistoryBeforePlanningFrame();
    TestExplicitObjectOnlyFallback();
    TestOptionalInputsAreNotMandatory();
    return 0;
}
