bin_PROGRAMS = halfserv
halfserv_SOURCES = halfserv.cpp md5.cpp mortuary_jaintor.cpp \
	secretarsha_Lena.cpp session_state.cpp srvProbe.cpp

# set the include path found by configure
INCLUDES= $(all_includes)

# the library search path.
halfserv_LDFLAGS = $(all_libraries) 
halfserv_LDADD = -lpthread -lpqxx
