-- A solution contains projects, and defines the available configurations
solution "fft_sandbox"
   configurations { "Debug", "Release" }
 
   -- A project defines one build target
   project "fft"
      kind "StaticLib"
      language "C++"
      files { "fourier.h", "fourier.cpp" }
      buildoptions { "--std=c++11" }
 
      configuration "Debug"
         defines { "DEBUG" }
         flags { "Symbols" }
 
      configuration "Release"
         defines { "NDEBUG" }
         flags { "Optimize" }    
         

