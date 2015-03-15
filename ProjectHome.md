WebDMA was created to allow our FIRST Robotics team to tune our robot in an easy to use and intuitive way via any modern web browser.

Using C++ operator overloading, WebDMA provides proxy objects that your application can use as normal variables which can be manipulated or displayed by your application via a configurable jQuery/javascript powered AJAX-enabled Web 2.0 interface hosted by an lightweight embedded web server.

FRC teams can install a binary release of WebDMA to their robot using the installer on the downloads page. This sets up the build environment and also installs a sample program to the Wind River Workbench.

Despite that WebDMA was specifically created for use in FIRST Robotics on the NI-cRio/vxWorks platform, it uses the Boost ASIO portable networking library and Boost Thread portable threads library and is **usable on any platform** supported by these Boost libraries (tested on Boost 1.38, requires a patch for vxWorks). A demo program is available that is compilable on Linux (using GNU Autotools) and Windows (using Visual Studio 2008).

A non-functional (but very shiny) demo of the interface is available at http://www.virtualroadside.com/botface/index.html

You can also see a video of WebDMA controlling our robot on YouTube: http://www.youtube.com/watch?v=sjbSHEmchIQ