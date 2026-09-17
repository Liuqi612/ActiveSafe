

#pragma once

#include <memory>
#include <sstream>
#include <utility>

#include <absl/base/attributes.h>
#include <absl/status/status.h>
#include <absl/strings/string_view.h>

namespace pnc_x {

class ABSL_MUST_USE_RESULT StatusBuilder {
 public:
    StatusBuilder(const StatusBuilder &sb);
    StatusBuilder(StatusBuilder &&sb) = default;
    StatusBuilder &operator=(const StatusBuilder &sb);
    StatusBuilder &operator=(StatusBuilder &&sb) = default;

    explicit StatusBuilder(const absl::Status &original_status);

    explicit StatusBuilder(absl::Status &&original_status);

    explicit StatusBuilder(absl::StatusCode code);

    ~StatusBuilder() = default;

    bool ok() const;

    template <typename T>
    T Returns(T &&val) const;

    void Void() const;

    StatusBuilder &SetAppend();

    StatusBuilder &SetPrepend();

    StatusBuilder &SetNoLogging();

    StatusBuilder &operator<<(const StatusBuilder &other);

    template <typename T>
    StatusBuilder &operator<<(const T &msg) {
        if (status_.ok()) { return *this; }
        *stream_ << msg;
        return *this;
    }

    operator absl::Status() const &;
    operator absl::Status() &&;

    absl::Status JoinMessageToStatus() const;

 private:
    enum class MessageJoinStyle {
        kAnnotate,
        kAppend,
        kPrepend,
    };

    absl::Status status_;
    bool no_logging_ = false;

    std::unique_ptr<std::ostringstream> stream_;

    MessageJoinStyle join_style_ = MessageJoinStyle::kAnnotate;
};

StatusBuilder AlreadyExistsErrorBuilder();

StatusBuilder FailedPreconditionErrorBuilder();

StatusBuilder InternalErrorBuilder();

StatusBuilder InvalidArgumentErrorBuilder();

StatusBuilder NotFoundErrorBuilder();

StatusBuilder UnavailableErrorBuilder();

StatusBuilder UnimplementedErrorBuilder();

StatusBuilder UnknownErrorBuilder();

}  // namespace pnc_x
