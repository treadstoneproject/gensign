# debug, optimized
AM_CXXFLAGS   = -I$(top_srcdir)/src/ -std=c++0x @AM_CXXFLAGS@

# Make src file 
# Get signature from Clamav and Generate signature support HNMAV system.
lib_LIBRARIES = libgensign.a

#@install header to system
libgensign_adir = $(includedir)/gensign

#Header
libgensign_a_HEADERS = clamavsig.hpp

# library
libgensign_a_SOURCES = $(libfilestructure_a_HEADERS)  clamavsig.cpp
