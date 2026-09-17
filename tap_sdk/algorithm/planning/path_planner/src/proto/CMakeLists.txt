cmake_minimum_required(VERSION 3.15)
project(pnc_proto VERSION 0.1.0 LANGUAGES C CXX)

set(PATH_SOURCE_3RDPARTY "/opt/senseauto_active/senseauto-3rdparty/3rdparty")
set(PLATFORM_NAME "x86_64")

set(PROTOC_ENV LD_LIBRARY_PATH=${PATH_SOURCE_3RDPARTY}/protobuf/bin/)
set(PROTOC_BIN ${PATH_SOURCE_3RDPARTY}/protobuf/bin/protoc)

file(GLOB PROTO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")

set(PROTO_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/build/generated)
file(MAKE_DIRECTORY ${PROTO_OUTPUT_DIR})

set(PROTO_SRCS "")
set(PROTO_HDRS "")

foreach(PROTO_FILE ${PROTO_FILES})
    get_filename_component(PROTO_FILENAME_WE ${PROTO_FILE} NAME_WE)
    set(GENERATED_SRC "${PROTO_OUTPUT_DIR}/${PROTO_FILENAME_WE}.pb.cc")
    set(GENERATED_HDR "${PROTO_OUTPUT_DIR}/${PROTO_FILENAME_WE}.pb.h")

    list(APPEND PROTO_SRCS ${GENERATED_SRC})
    list(APPEND PROTO_HDRS ${GENERATED_HDR})

    add_custom_command(
        OUTPUT ${GENERATED_SRC} ${GENERATED_HDR}
        COMMAND ${CMAKE_COMMAND} -E env ${PROTOC_ENV} ${PROTOC_BIN}
        --proto_path=${CMAKE_CURRENT_SOURCE_DIR}
        --cpp_out=${PROTO_OUTPUT_DIR}
        ${PROTO_FILE}
        DEPENDS ${PROTO_FILE}
        COMMENT "Generating C++ protobuf sources from ${PROTO_FILE}"
        VERBATIM
    )
endforeach()

add_library(pnc_proto STATIC ${PROTO_SRCS} ${PROTO_HDRS})

target_compile_options(pnc_proto PRIVATE -Wno-deprecated-declarations)

target_include_directories(pnc_proto PUBLIC
    ${PROTO_OUTPUT_DIR}
    ${3rdparty_includes} # 你需要先定义
)

target_link_libraries(pnc_proto PUBLIC
    ${3rdparty_libraries} # 你需要先定义
)

add_custom_target(proto_target ALL DEPENDS ${PROTO_SRCS} ${PROTO_HDRS})

# 生成Python代码
set(PROTO_PYTHON_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/build/python)
file(MAKE_DIRECTORY ${PROTO_PYTHON_OUTPUT_DIR})

set(PROTO_GENERATED_PY "")

set_source_files_properties(
    ${CMAKE_BINARY_DIR}/generated/autonomy_state.pb.cc
    PROPERTIES COMPILE_FLAGS "-Wno-deprecated-declarations"
)

foreach(PROTO_FILE ${PROTO_FILES})
    get_filename_component(PROTO_FILENAME_WE ${PROTO_FILE} NAME_WE)
    set(GENERATED_PY "${PROTO_PYTHON_OUTPUT_DIR}/${PROTO_FILENAME_WE}_pb2.py")

    add_custom_command(
        OUTPUT ${GENERATED_PY}
        COMMAND ${CMAKE_COMMAND} -E env ${PROTOC_ENV} ${PROTOC_BIN}
        --proto_path=${CMAKE_CURRENT_SOURCE_DIR}
        --python_out=${PROTO_PYTHON_OUTPUT_DIR}
        ${PROTO_FILE}
        DEPENDS ${PROTO_FILE}
        COMMENT "Generating Python protobuf source from ${PROTO_FILE}"
        VERBATIM
    )
    list(APPEND PROTO_GENERATED_PY ${GENERATED_PY})
endforeach()

add_custom_target(proto_python ALL DEPENDS ${PROTO_GENERATED_PY})

install(FILES ${PROTO_HDRS} DESTINATION include)
install(DIRECTORY ${PROTO_PYTHON_OUTPUT_DIR}/ DESTINATION python)
