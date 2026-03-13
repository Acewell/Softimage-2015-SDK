# this makefile is to be used with gmake

# Global variables
include $(XSISDK_ROOT)/mkfiles/vars.gnu

INCLUDES += -I.

SYSLIBS := -lGL -lCg -lCgGL

LDFLAGS += -L$(XSI_HOME)/../Application/bin -L$(XSISDK_ROOT)/../Application/bin

# Sources to be compiled
SOURCES := \
	DepthOfField.cpp \
	bufferDrawPass.cpp \
	depthOfFieldView.cpp \
	frameBuffer.cpp \
	GLee.cpp \
   $(END_OF_LIST)

# Target
# Note: Depending where the source code
# is located you may want to adjust this line to 
# output directly into your /Application/Plugins directory
# example SOTARGETS  := ../Application/Plugins/DepthOfField.so

SOTARGETS  := ../Application/Plugins/DepthOfField$(BITEXT).so

# Global rules
include $(XSISDK_ROOT)/mkfiles/rules.gnu

# Specific dependencies
$(SOTARGETS): $(ALLOBJECTS) $(XSISDKLIBS)
$(CXXOBJECTS): $(OBJDIR)/%.o: %.cpp
$(COBJECTS): $(OBJDIR)/%.o: %.c

