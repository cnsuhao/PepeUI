
# List all source files into string ${SRCS}
file( GLOB SRCS *.c *.h *.cpp *.hpp ) 

# Add the main executable
add_executable( ${ExeName} ${SRCS} )

# Link libraries
# Windows
    if(MSVC)


    endif(MSVC)

# OS X
    if(APPLE)
    
    endif(APPLE)
    

# Linux
    if(UNIX AND NOT APPLE)
        # SDL2 for cross-platform windowing
        find_package (SDL2 REQUIRED)
        
        # GLM for vector/matrix mathematics
        find_package (GLM REQUIRED)
        
        if (SDL2_FOUND)
            if (GLM_FOUND)
                # SDL2 path handling
                string(REGEX REPLACE "/SDL2" "" SDL_INCLUDE_OUT "${SDL2_INCLUDE_DIRS}")
                string(REGEX REPLACE "SDL2 " "SDL2" SDL_OUT "${SDL2_LIBRARIES}")
                MESSAGE("SDL2 Include: ${SDL_INCLUDE_OUT}.")
                MESSAGE("SDL2 Libraries: ${SDL_OUT}.")

                # Link and add search paths
                target_include_directories(${ExeName} PUBLIC "${SDL_INCLUDE_OUT}" "${GLM_INCLUDE_DIRS}")
                SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g" )
                target_link_libraries(${ExeName} ${SDL_OUT} "-lGL")
            endif (GLM_FOUND)
        endif (SDL2_FOUND)
    endif(UNIX AND NOT APPLE)



# Install the main executable
install(TARGETS ${ExeName} RUNTIME DESTINATION bin)
