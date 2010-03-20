
AUTOMAKE_OPTIONS = foreign

INCLUDES = -I../include

lib_LTLIBRARIES = libWebDMA.la

libWebDMA_la_LDFLAGS = $(BOOST_SYSTEM_LDFLAGS) $(BOOST_THREAD_LDFLAGS)

libWebDMA_la_LIBADD = $(BOOST_SYSTEM_LIBS) $(BOOST_THREAD_LIBS)

libWebDMA_la_SOURCES = \
	WebDMA/DataProxyInfo.h \
	WebDMA/StaticDeleter.h \
	WebDMA/VariableProxy.cpp \
	WebDMA/WebDMA.cpp \
	WebDMA/WebDMA_Pimpl.cpp \
	WebDMA/WebDMA_Pimpl.h \
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


extra_DIST = \
	boost/system/src/error_code.cpp \
	boost/system/src/Makefile \
	boost/system/Makefile \
	boost/boost_1_38_vxworks.patch \
	boost/LICENSE_1_0.txt \
	boost/thread/src/pthread/once.cpp \
	boost/thread/src/pthread/Makefile \
	boost/thread/src/pthread/timeconv.inl \
	boost/thread/src/pthread/exceptions.cpp \
	boost/thread/src/pthread/thread.cpp \
	boost/thread/src/tss_null.cpp \
	boost/thread/src/Makefile \
	boost/thread/Makefile
	

