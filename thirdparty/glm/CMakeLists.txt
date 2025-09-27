cmake_minimum_required(VERSION 3.10)

set(GLM_SOURCE_DIR "include/glm")

file(GLOB ROOT_SOURCE ${GLM_SOURCE_DIR}/*.cpp)
file(GLOB ROOT_INLINE ${GLM_SOURCE_DIR}/*.inl)
file(GLOB ROOT_HEADER ${GLM_SOURCE_DIR}/*.hpp)

file(GLOB_RECURSE CORE_SOURCE ${GLM_SOURCE_DIR}/detail/*.cpp)
file(GLOB_RECURSE CORE_INLINE ${GLM_SOURCE_DIR}/detail/*.inl)
file(GLOB_RECURSE CORE_HEADER ${GLM_SOURCE_DIR}/detail/*.hpp)

file(GLOB_RECURSE EXT_SOURCE ${GLM_SOURCE_DIR}/ext/*.cpp)
file(GLOB_RECURSE EXT_INLINE ${GLM_SOURCE_DIR}/ext/*.inl)
file(GLOB_RECURSE EXT_HEADER ${GLM_SOURCE_DIR}/ext/*.hpp)

file(GLOB_RECURSE GTC_SOURCE ${GLM_SOURCE_DIR}/gtc/*.cpp)
file(GLOB_RECURSE GTC_INLINE ${GLM_SOURCE_DIR}/gtc/*.inl)
file(GLOB_RECURSE GTC_HEADER ${GLM_SOURCE_DIR}/gtc/*.hpp)

file(GLOB_RECURSE GTX_SOURCE ${GLM_SOURCE_DIR}/gtx/*.cpp)
file(GLOB_RECURSE GTX_INLINE ${GLM_SOURCE_DIR}/gtx/*.inl)
file(GLOB_RECURSE GTX_HEADER ${GLM_SOURCE_DIR}/gtx/*.hpp)

file(GLOB_RECURSE SIMD_SOURCE ${GLM_SOURCE_DIR}/simd/*.cpp)
file(GLOB_RECURSE SIMD_INLINE ${GLM_SOURCE_DIR}/simd/*.inl)
file(GLOB_RECURSE SIMD_HEADER ${GLM_SOURCE_DIR}/simd/*.h)

source_group("Core Files" FILES ${CORE_SOURCE})
source_group("Core Files" FILES ${CORE_INLINE})
source_group("Core Files" FILES ${CORE_HEADER})
source_group("EXT Files"  FILES ${EXT_SOURCE})
source_group("EXT Files"  FILES ${EXT_INLINE})
source_group("EXT Files"  FILES ${EXT_HEADER})
source_group("GTC Files"  FILES ${GTC_SOURCE})
source_group("GTC Files"  FILES ${GTC_INLINE})
source_group("GTC Files"  FILES ${GTC_HEADER})
source_group("GTX Files"  FILES ${GTX_SOURCE})
source_group("GTX Files"  FILES ${GTX_INLINE})
source_group("GTX Files"  FILES ${GTX_HEADER})
source_group("SIMD Files" FILES ${SIMD_SOURCE})
source_group("SIMD Files" FILES ${SIMD_INLINE})
source_group("SIMD Files" FILES ${SIMD_HEADER})

add_library(glm
    ${ROOT_SOURCE}    ${ROOT_INLINE}    ${ROOT_HEADER}
    ${CORE_SOURCE}    ${CORE_INLINE}    ${CORE_HEADER}
    ${EXT_SOURCE}     ${EXT_INLINE}     ${EXT_HEADER}
    ${GTC_SOURCE}     ${GTC_INLINE}     ${GTC_HEADER}
    ${GTX_SOURCE}     ${GTX_INLINE}     ${GTX_HEADER}
    ${SIMD_SOURCE}    ${SIMD_INLINE}    ${SIMD_HEADER}
)

target_include_directories(glm PUBLIC "include")
add_library(glm::glm ALIAS glm)
