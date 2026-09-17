

#include <string>

#include "util/status_builder.h"
#include <absl/memory/memory.h>
#include <absl/strings/str_cat.h>

namespace pnc_x {

StatusBuilder::StatusBuilder(const StatusBuilder &sb) {
    status_ = sb.status_;
    no_logging_ = sb.no_logging_;
    stream_ = absl::make_unique<std::ostringstream>(sb.stream_->str());
    join_style_ = sb.join_style_;
}

StatusBuilder &StatusBuilder::operator=(const StatusBuilder &sb) {
    if (this == &sb) {
        return *this;
    }
    status_ = sb.status_;
    no_logging_ = sb.no_logging_;
    stream_ = absl::make_unique<std::ostringstream>(sb.stream_->str());
    join_style_ = sb.join_style_;
    return *this;
}

StatusBuilder &StatusBuilder::SetAppend() {
    if (status_.ok()) {
        return *this;
    }
    join_style_ = MessageJoinStyle::kAppend;
    return *this;
}

StatusBuilder &StatusBuilder::SetPrepend() {
    if (status_.ok()) {
        return *this;
    }
    join_style_ = MessageJoinStyle::kPrepend;
    return *this;
}

StatusBuilder &StatusBuilder::SetNoLogging() {
    no_logging_ = true;
    return *this;
}

StatusBuilder::operator absl::Status() const & {
    if (stream_->str().empty() || no_logging_) {
        return status_;
    }
    return static_cast<pnc_x::StatusBuilder>(StatusBuilder(*this))
        .JoinMessageToStatus();
}

StatusBuilder::operator absl::Status() && {
    if (stream_->str().empty() || no_logging_) {
        return status_;
    }
    return JoinMessageToStatus();
}

absl::Status StatusBuilder::JoinMessageToStatus() const {
    std::string message;
    if (join_style_ == MessageJoinStyle::kAnnotate) {
        if (!status_.ok()) {
            message = absl::StrCat(status_.message(), "; ", stream_->str());
        }
    } else {
        message = join_style_ == MessageJoinStyle::kPrepend
                      ? absl::StrCat(stream_->str(), status_.message())
                      : absl::StrCat(status_.message(), stream_->str());
    }
    return absl::Status(status_.code(), message);
}

StatusBuilder::StatusBuilder(const absl::Status &original_status)
    : status_(original_status), stream_(new std::ostringstream) {}

StatusBuilder::StatusBuilder(absl::Status &&original_status)
    : status_(std::move(original_status)), stream_(new std::ostringstream) {}

StatusBuilder::StatusBuilder(absl::StatusCode code)
    : status_(code, ""), stream_(new std::ostringstream) {}

bool StatusBuilder::ok() const { return status_.ok(); }

template <typename T>
T StatusBuilder::Returns(T &&val) const {
    return std::forward<T>(val);
}

void StatusBuilder::Void() const {}

StatusBuilder &StatusBuilder::operator<<(const StatusBuilder &other) {
    static_cast<void>(other);
    return *this;
}

StatusBuilder AlreadyExistsErrorBuilder() {
    return static_cast<pnc_x::StatusBuilder>(
        StatusBuilder(absl::StatusCode::kAlreadyExists));
}

StatusBuilder FailedPreconditionErrorBuilder() {
    return static_cast<pnc_x::StatusBuilder>(
        StatusBuilder(absl::StatusCode::kFailedPrecondition));
}

StatusBuilder InternalErrorBuilder() {
    return static_cast<pnc_x::StatusBuilder>(
        StatusBuilder(absl::StatusCode::kInternal));
}

StatusBuilder InvalidArgumentErrorBuilder() {
    return static_cast<pnc_x::StatusBuilder>(
        StatusBuilder(absl::StatusCode::kInvalidArgument));
}

StatusBuilder NotFoundErrorBuilder() {
    return static_cast<pnc_x::StatusBuilder>(
        StatusBuilder(absl::StatusCode::kNotFound));
}

StatusBuilder UnavailableErrorBuilder() {
    return static_cast<pnc_x::StatusBuilder>(
        StatusBuilder(absl::StatusCode::kUnavailable));
}

StatusBuilder UnimplementedErrorBuilder() {
    return static_cast<pnc_x::StatusBuilder>(
        StatusBuilder(absl::StatusCode::kUnimplemented));
}

StatusBuilder UnknownErrorBuilder() {
    return static_cast<pnc_x::StatusBuilder>(
        StatusBuilder(absl::StatusCode::kUnknown));
}

}  // namespace pnc_x
