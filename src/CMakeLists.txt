
# List all source files into string ${SRCS}
file( GLOB HSRCS *.h *.hpp ) 
file( GLOB SRCS *.c *.cpp ) 


# Add the main executable
add_executable( ${ExeName} ${HSRCS} ${SRCS} )

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

        # SDL_gpu for a high-level OpenGL wrapper
        #   
        #   Currently there is no FindSDL_gpu module so
        #   linking is manually done
        #   
        #   find_package (SDL_gpu)
        #
        # SDL_ttf for text rendering
        #   
        #   Currently linked manually   
        #
        #   find_package(SDL_ttf REQUIRED)
                
        
        MESSAGE("SDLTTF Include: ${SDL2_TTF_INCLUDE_OUT}.")
        # Make sure everything is found correctly
        if (SDL2_FOUND AND GLM_FOUND)
            # SDL2 path handling
            string(REGEX REPLACE "/SDL2" "" SDL_INCLUDE_OUT "${SDL2_INCLUDE_DIRS}")
            string(REGEX REPLACE "SDL2 " "SDL2" SDL_OUT "${SDL2_LIBRARIES}")
            
            # Debug messages
            MESSAGE("SDL2 Include: ${SDL_INCLUDE_OUT}.")
            MESSAGE("SDL2 Libraries: ${SDL_OUT}.")
            MESSAGE("SDLGPU LIBRARY PPATH: ${SDL_GPU_LIBRARIES}")
            
            # Add include directories
            target_include_directories(${ExeName} PUBLIC "${SDL_INCLUDE_OUT}" "${GLM_INCLUDE_DIRS}" "/usr/include/")
            
            # Set compiler flags
            SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g" )
            
            # Link libraries
            target_link_libraries(${ExeName} 
            ${SDL_OUT} 
            #${SDL_GPU_LIBRARIES}
            "-lSDL2_ttf"
            "-lSDL2_gpu"
            "-lGL")
                                        
        endif (SDL2_FOUND AND GLM_FOUND)
    endif(UNIX AND NOT APPLE)



# Install the main executable
install(TARGETS ${ExeName} RUNTIME DESTINATION bin)
