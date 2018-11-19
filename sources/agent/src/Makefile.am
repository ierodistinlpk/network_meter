bin_PROGRAMS = agent_nix
agent_nix_SOURCES = Agent.cpp Cycle.cpp NetEvent.cpp NetResult.cpp Post.cpp \
	Probe.cpp agent_nix.cpp crc.cpp md5.cpp pingovator.cpp

# set the include path found by configure
INCLUDES= $(all_includes)

# the library search path.
agent_nix_LDFLAGS = $(all_libraries) 
agent_nix_DEPENDENCIES = -lpthread
agent_nix_LDADD = -lpthread
