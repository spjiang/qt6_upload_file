# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\video_upload_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\video_upload_autogen.dir\\ParseCache.txt"
  "video_upload_autogen"
  )
endif()
