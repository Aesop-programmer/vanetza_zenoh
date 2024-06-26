if(NOT TARGET Boost::system)
    message(STATUS "Skip build of socktap because of missing Boost::system dependency")
    return()
endif()

if(NOT TARGET Boost::program_options)
    message(STATUS "Skip build of socktap because of missing Boost::program_options dependency")
    return()
endif()

find_package(Threads REQUIRED)

set(CXX_SOURCES
    application.cpp
    benchmark_application.cpp
    cam_application.cpp
    dcc_passthrough.cpp
    ethernet_device.cpp
    hello_application.cpp
    link_layer.cpp
    positioning.cpp
    raw_socket_link.cpp
    router_context.cpp
    security.cpp
    tcp_link.cpp
    time_trigger.cpp
    udp_link.cpp
    btpb_write.cpp
    read_application.cpp
    btpb_read.cpp
)
add_vanetza_component(btp_write ${CXX_SOURCES})
target_link_libraries(btp_write PUBLIC Boost::system Boost::program_options Threads::Threads vanetza)





##install(TARGETS btp_write EXPORT ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})

find_file(COHDA_LLC_API_HEADER llc-api.c
    PATHS "/home/duser"
    PATH_SUFFIXES "cohda/kernel/include/linux/cohda/llc"
    CMAKE_FIND_ROOT_PATH_BOTH
    DOC "Cohda LLC API header")
mark_as_advanced(COHDA_LLC_API_HEADER)
if(COHDA_LLC_API_HEADER)
    set(COHDA_LLC_API_FOUND ON)
else()
    set(COHDA_LLC_API_FOUND OFF)
endif()

option(SOCKTAP_WITH_COHDA_LLC "Enable Cohda LLC link layer for socktap" ${COHDA_LLC_API_FOUND})
if(SOCKTAP_WITH_COHDA_LLC)
    if(NOT COHDA_LLC_API_HEADER)
        message(SEND_ERROR "Cohda LLC API header [llc-api.h] is missing")
    endif()
    get_filename_component(COHDA_LLC_INCLUDE_DIR ${COHDA_LLC_API_HEADER} DIRECTORY)
    target_compile_definitions(btp_write PUBLIC "SOCKTAP_WITH_COHDA_LLC")
    target_include_directories(btp_write PUBLIC ${COHDA_LLC_INCLUDE_DIR})
    target_sources(btp_write PRIVATE cohda.cpp cohda_link.cpp)
endif()

# find_package(GPS QUIET)
# option(SOCKTAP_WITH_GPSD "Enable gpsd positioning for socktap" ${GPS_FOUND})
# if(SOCKTAP_WITH_GPSD)
#     find_package(GPS REQUIRED)
#     target_compile_definitions(btp_write PUBLIC "SOCKTAP_WITH_GPSD")
#     target_link_libraries(btp_write PUBLIC GPS::GPS)
#     target_sources(btp_write PRIVATE gps_position_provider.cpp)
# endif()
