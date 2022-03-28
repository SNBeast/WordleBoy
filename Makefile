#
# A Makefile that compiles all .c in "source" and "words" subdirectories
# and all .s files in the "asm" subdirectory and places the output in
# an "objects" subdirectory
#

# If you move this project you can change the directory 
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"
GBDK_HOME = C:/GBDK/

LCC = $(GBDK_HOME)bin/lcc

# You can set flags for LCC here
LCCFLAGS = -Wall -Wl-ya1 -Wl-yoA -Wl-yt0x10 -Wm-yn"WORDLEBOY" -Iinclude -autobank

# -Wl-ya1: 1 external RAM bank
# -Wl-yoA: Automatic number of ROM banks
# -Wl-yt0x10: Cartridge mapper 0x10 (MBC3 with persistent RAM and RTC)
# -Wm-yn"WORDLEBOY": Set title in header to WORDLEBOY
# -autobank: in translation units assigned to bank 255, automatically assign them banks

# You can set the name of the .gb ROM file here
PROJECTNAME = WordleBoy

# ASMDIR		= asm
SRCDIR      = source
OBJDIR      = objects
WORDDIR     = words
BINS	    = $(PROJECTNAME).gb
CSOURCES    = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(WORDDIR),$(notdir $(wildcard $(dir)/*.c)))
# ASMSOURCES  = $(foreach dir,$(ASMDIR),$(notdir $(wildcard $(dir)/*.s)))
# OBJS        = $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.s=$(OBJDIR)/%.o)
OBJS        = $(CSOURCES:%.c=$(OBJDIR)/%.o)

all:	prepare $(BINS)

compile.bat: Makefile
	@echo "REM Automatically generated from Makefile" > compile.bat
	@make -sn | sed y/\\//\\\\/ | grep -v make >> compile.bat

# Compile .c files in "source/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.c
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# Compile .c files in "words/" to .o object files
$(OBJDIR)/%.o:	$(WORDDIR)/%.c
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# Compile .s assembly files in "asm/" to .o object files
# $(OBJDIR)/%.o:	$(ASMDIR)/%.s
#	$(LCC) $(LCCFLAGS) -c -o $@ $<

# If needed, compile .c files in "source/" to .s assembly files
# (not required if .c is compiled directly to .o)
$(OBJDIR)/%.s:	$(SRCDIR)/%.c
	$(LCC) $(LCCFLAGS) -S -o $@ $<

# Link the compiled object files into a .gb ROM file
$(BINS):	$(OBJS)
	$(LCC) $(LCCFLAGS) -o $(BINS) $(OBJS)

prepare:
	mkdir -p $(OBJDIR)

clean:
	rm -f  *.gb *.ihx *.cdb *.adb *.noi *.map *.sym
	rm -rf  $(OBJDIR)
