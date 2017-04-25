catkin_add_gtest(provider_thruster_test provider_thruster_test.cc ${provider_thruster_FILES})
target_link_libraries(provider_thruster_test ${catkin_LIBRARIES} ${Boost_LIBRARIES})
set_target_properties(provider_thruster_test PROPERTIES LINKER_LANGUAGE CXX )