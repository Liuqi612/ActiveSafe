
#pragma once

#include <string>
#include <utility>
#include <vector>

#include "container/strong_vector.h"
#include "pncx_initializer.pb.h"
#include "initializer/geometry/geometry_form.h"
#include "math/vec.h"
#include <absl/strings/str_format.h>
#include <absl/types/span.h>
#include "common/log.h"

namespace pnc_x {
namespace planning {

DECLARE_STRONG_VECTOR(GeometryNode);
DECLARE_STRONG_VECTOR(GeometryEdge);

struct GeometryNode {
    GeometryNodeIndex index;
    Vec2d xy;
    double k;
    int station_index = 0;
    double lateral_offset = 0.0;
    double accumulated_s = 0.0;

    bool reachable = false;
    bool resampled = false;

    bool active = true;

    std::string DebugString() const {
        return absl::StrFormat(
            "GeometryNode %d(x: %.2f, y: %.2f, k: %.2f, station_index: %d, "
            "accumulated_s: %.2f, reachable: %d, resampled: %d, active: %d)",
            index.value(), xy.x(), xy.y(), k, station_index, accumulated_s,
            reachable, resampled, active);
    }
};

struct GeometryEdge {
    GeometryEdgeIndex index;
    GeometryNodeIndex start;
    GeometryNodeIndex end;
    const GeometryForm *geometry;
    bool truncated = false;

    bool active = true;

    bool isTruncated() const { return truncated; }
};

class GeometryGraph {
 public:
    virtual const GeometryNodeVector<GeometryNode> &nodes() const = 0;
    virtual absl::Span<const std::vector<GeometryNodeIndex>> nodes_layers()
        const = 0;
    virtual const GeometryNode &GetNode(GeometryNodeIndex index) const = 0;

    virtual const GeometryNode &GetStartNode() const = 0;
    virtual const GeometryEdgeVector<GeometryEdge> &edges() const = 0;
    virtual const GeometryEdge &GetEdge(GeometryEdgeIndex index) const = 0;

    virtual absl::Span<const GeometryEdgeIndex> GetOutgoingEdges(
        GeometryNodeIndex index) const = 0;
    virtual double GetMaxAccumulatedS() const = 0;

    virtual const GeometryGraphProto::EndInfo &GetGeometryGraphEndInfo()
        const = 0;

    virtual void DeactivateNode(GeometryNodeIndex) = 0;
    virtual void DeactivateEdge(GeometryEdgeIndex) = 0;

    virtual bool IsActive(GeometryNodeIndex) const = 0;
    virtual bool IsActive(GeometryEdgeIndex) const = 0;

    virtual ~GeometryGraph() {}

    virtual void ToProto(GeometryGraphProto *proto) const = 0;
};

class XYGeometryGraph : public GeometryGraph {
 public:
    XYGeometryGraph() = default;
    XYGeometryGraph(
        GeometryNodeVector<GeometryNode> local_nodes,
        std::vector<std::vector<GeometryNodeIndex>> local_nodes_layers,
        GeometryEdgeVector<GeometryEdge> local_edges,
        GeometryNodeVector<std::vector<GeometryEdgeIndex>> outgoing_edges,
        GeometryGraphProto::EndInfo end_info)
        : nodes_(std::move(local_nodes)),
          nodes_layers_(std::move(local_nodes_layers)),
          edges_(std::move(local_edges)),
          nodes_outgoing_edges_(std::move(outgoing_edges)),
          end_info_(std::move(end_info)) {}

    void ToProto(GeometryGraphProto *proto) const override;

    const GeometryNodeVector<GeometryNode> &nodes() const override {
        return nodes_;
    }
    const GeometryNode &GetNode(GeometryNodeIndex index) const override {
        return nodes_[index];
    }
    const GeometryNode &GetStartNode() const override;
    const GeometryEdgeVector<GeometryEdge> &edges() const override {
        return edges_;
    }
    const GeometryEdge &GetEdge(GeometryEdgeIndex index) const override {
        return edges_[index];
    }

    absl::Span<const std::vector<GeometryNodeIndex>> nodes_layers()
        const override {
        return nodes_layers_;
    }

    absl::Span<const GeometryEdgeIndex> GetOutgoingEdges(
        GeometryNodeIndex index) const override {
        return nodes_outgoing_edges_[index];
    }

    double GetMaxAccumulatedS() const override;

    const GeometryGraphProto::EndInfo &GetGeometryGraphEndInfo()
        const override {
        return end_info_;
    }

    inline void DeactivateNode(GeometryNodeIndex index) override {
        nodes_[index].active = false;
    }

    inline void DeactivateEdge(GeometryEdgeIndex index) override {
        edges_[index].active = false;
    }

    bool IsActive(GeometryNodeIndex index) const override {
        return nodes_[index].active;
    }
    bool IsActive(GeometryEdgeIndex index) const override {
        return edges_[index].active;
    }

 private:
    GeometryNodeVector<GeometryNode> nodes_;

    std::vector<std::vector<GeometryNodeIndex>> nodes_layers_;
    GeometryEdgeVector<GeometryEdge> edges_;

    GeometryNodeVector<std::vector<GeometryEdgeIndex>> nodes_outgoing_edges_;

    GeometryGraphProto::EndInfo end_info_;
};

}  // namespace planning
}  // namespace pnc_x
