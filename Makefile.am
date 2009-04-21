

AUTOMAKE_OPTIONS = 1.6 foreign

bin_PROGRAMS = webface

webface_LDFLAGS = $(BOOST_SYSTEM_LDFLAGS) $(BOOST_THREAD_LDFLAGS)

webface_LDADD = $(BOOST_SYSTEM_LIBS) $(BOOST_THREAD_LIBS)

webface_SOURCES = \
	main.cpp \
	WebDMA/DataProxyInfo.h \
	WebDMA/StaticDeleter.h \
	WebDMA/VariableProxy.h \
	WebDMA/VariableProxyFlags.h \
	WebDMA/WebInterface.cpp \
	WebDMA/WebInterface.h \
	WebDMA/server/connection.cpp \
	WebDMA/server/connection.hpp \
	WebDMA/server/connection_manager.cpp \
	WebDMA/server/connection_manager.hpp \
	WebDMA/server/header.hpp \
	WebDMA/server/mime_types.cpp \
	WebDMA/server/mime_types.hpp \
	WebDMA/server/reply.cpp \
	WebDMA/server/reply.hpp \
	WebDMA/server/request.hpp \
	WebDMA/server/request_handler.cpp \
	WebDMA/server/request_handler.hpp \
	WebDMA/server/request_parser.cpp \
	WebDMA/server/request_parser.hpp \
	WebDMA/server/server.cpp \
	WebDMA/server/server.hpp
	

