
#pragma once

#include <string>
#include <vector>

#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include <google/protobuf/message.h>

namespace pnc_x {
namespace file_util {

absl::Status RemoveFile(std::string filepath);

absl::Status CreateDirectory(std::string dir);

absl::Status RemoveDirectory(std::string dir);

absl::StatusOr<std::vector<std::string>> ListDirectory(std::string dir);

absl::StatusOr<std::vector<std::string>> ListDirectoryRecursive(
    std::string dir);

bool GetFileContent(const std::string &filename, std::string *content);

bool GetFileContentByGetline(const std::string &filename, std::string *content);

std::string GetFileContentOrDie(const std::string &filename);

bool SetFileContent(const std::string &content, const std::string &filename);

void SetFileContentOrDie(const std::string &content,
                         const std::string &filename);

std::string GetFileExtension(const std::string &filename);

bool StringToProto(const std::string &proto_string,
                   google::protobuf::Message *proto);

bool TextFileToProto(const std::string &file_name,
                     google::protobuf::Message *message);

bool BinaryFileToProto(const std::string &filename,
                       google::protobuf::Message *proto);

bool FileToProto(const std::string &filename, google::protobuf::Message *proto);

bool ProtoToTextFile(const google::protobuf::Message &proto,
                     const std::string &filename);

bool ProtoToBinaryFile(const google::protobuf::Message &proto,
                       const std::string &filename);

bool ProtoToJsonFile(const google::protobuf::Message &proto,
                     const std::string &filename);

}  // namespace file_util
}  // namespace pnc_x
