#!/usr/bin/env python3

import os
import sys
import subprocess

# Copyright (c) André Burgaud
# http://www.burgaud.com/bring-colors-to-the-windows-console-with-python/
if sys.platform == "win32":
    from ctypes import windll, Structure, c_short, c_ushort, byref

    SHORT = c_short
    WORD = c_ushort

    class COORD(Structure):
      """struct in wincon.h."""
      _fields_ = [
        ("X", SHORT),
        ("Y", SHORT)]

    class SMALL_RECT(Structure):
      """struct in wincon.h."""
      _fields_ = [
        ("Left", SHORT),
        ("Top", SHORT),
        ("Right", SHORT),
        ("Bottom", SHORT)]

    class CONSOLE_SCREEN_BUFFER_INFO(Structure):
      """struct in wincon.h."""
      _fields_ = [
        ("dwSize", COORD),
        ("dwCursorPosition", COORD),
        ("wAttributes", WORD),
        ("srWindow", SMALL_RECT),
        ("dwMaximumWindowSize", COORD)]

    # winbase.h
    STD_INPUT_HANDLE = -10
    STD_OUTPUT_HANDLE = -11
    STD_ERROR_HANDLE = -12

    # wincon.h
    FOREGROUND_BLACK     = 0x0000
    FOREGROUND_BLUE      = 0x0001
    FOREGROUND_GREEN     = 0x0002
    FOREGROUND_CYAN      = 0x0003
    FOREGROUND_RED       = 0x0004
    FOREGROUND_MAGENTA   = 0x0005
    FOREGROUND_YELLOW    = 0x0006
    FOREGROUND_GREY      = 0x0007
    FOREGROUND_INTENSITY = 0x0008 # foreground color is intensified.

    BACKGROUND_BLACK     = 0x0000
    BACKGROUND_BLUE      = 0x0010
    BACKGROUND_GREEN     = 0x0020
    BACKGROUND_CYAN      = 0x0030
    BACKGROUND_RED       = 0x0040
    BACKGROUND_MAGENTA   = 0x0050
    BACKGROUND_YELLOW    = 0x0060
    BACKGROUND_GREY      = 0x0070
    BACKGROUND_INTENSITY = 0x0080 # background color is intensified.

    stdout_handle = windll.kernel32.GetStdHandle(STD_OUTPUT_HANDLE)
    SetConsoleTextAttribute = windll.kernel32.SetConsoleTextAttribute
    GetConsoleScreenBufferInfo = windll.kernel32.GetConsoleScreenBufferInfo

    def get_text_attr():
      """Returns the character attributes (colors) of the console screen
      buffer."""
      csbi = CONSOLE_SCREEN_BUFFER_INFO()
      GetConsoleScreenBufferInfo(stdout_handle, byref(csbi))
      return csbi.wAttributes

    def set_text_attr(color):
      """Sets the character attributes (colors) of the console screen
      buffer. Color is a combination of foreground and background color,
      foreground and background intensity."""
      SetConsoleTextAttribute(stdout_handle, color)
###############################################################################

def color(color):
    """Set the color. Works on Win32 and normal terminals."""
    if sys.platform == "win32":
        if color == "green":
            set_text_attr(FOREGROUND_GREEN | get_text_attr() & 0x0070 | FOREGROUND_INTENSITY)
        elif color == "yellow":
            set_text_attr(FOREGROUND_YELLOW | get_text_attr() & 0x0070 | FOREGROUND_INTENSITY)
        elif color == "red":
            set_text_attr(FOREGROUND_RED | get_text_attr() & 0x0070 | FOREGROUND_INTENSITY)
        elif color == "blue":
            set_text_attr(FOREGROUND_BLUE | get_text_attr() & 0x0070 | FOREGROUND_INTENSITY)
        elif color == "reset":
            set_text_attr(FOREGROUND_GREY | get_text_attr() & 0x0070)
        elif color == "grey":
            set_text_attr(FOREGROUND_GREY | get_text_attr() & 0x0070)
    else :
        if color == "green":
            sys.stdout.write('\033[92m')
        elif color == "red":
            sys.stdout.write('\033[91m')
        elif color == "blue":
            sys.stdout.write('\033[94m')
        elif color == "reset":
            sys.stdout.write('\033[0m')

def print_error(msg):
    color("red")
    print ("ERROR: {}".format(msg))
    color("reset")

def print_blue(msg):
    color("blue")
    print(msg)
    color("reset")

def compile_extensions(extensions_root):
    originalDir = os.getcwd()

    try:
        print_blue("\nCompiling extensions in {}".format(extensions_root))

        # Prepare 32bit build dirs
        vcproj32 = os.path.join(extensions_root, "vcproj")
        if not os.path.exists(vcproj32):
            os.mkdir(vcproj32)
        # Build
        os.chdir(vcproj32)
        subprocess.call(["cmake", "..", "-DINTERCEPT_BUILD2RV=ON", "-G", "Visual Studio 15 2017"])
        print()
        subprocess.call(["msbuild", "Intercept.sln", "/m", "/p:Configuration=Debug"])

        # Prepare 64bit build dirs
        vcproj64 = os.path.join(extensions_root, "vcproj64")
        if not os.path.exists(vcproj64):
            os.mkdir(vcproj64)
        # Build
        os.chdir(vcproj64)
        subprocess.call(["cmake", "..", "-DINTERCEPT_BUILD2RV=ON", "-G", "Visual Studio 15 2017 Win64"])
        print()
        subprocess.call(["msbuild", "Intercept.sln", "/m", "/p:Configuration=Debug"])
    except:
        print_error("COMPILING EXTENSIONS.")
        raise
    finally:
        os.chdir(originalDir)

def main():
    print("""
  #########################
  # Intercept Extension Build #
  #########################
""")

    os.chdir(os.path.dirname(os.path.realpath(__file__)))
    root_parent = os.path.abspath(os.path.join(os.getcwd(), os.pardir))
    os.chdir(root_parent)
    compile_extensions(root_parent)

if __name__ == "__main__":
    sys.exit(main())
