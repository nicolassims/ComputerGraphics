# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.Lab2.Debug:
/Users/bhackney/Documents/Computer\ Graphics/Computer-Graphics-work/Lab3_Starfield/build/Debug/Lab2:\
	/Users/bhackney/Qt/5.14.0/clang_64/lib/QtOpenGL.framework/QtOpenGL\
	/Users/bhackney/Qt/5.14.0/clang_64/lib/QtWidgets.framework/QtWidgets\
	/Users/bhackney/Qt/5.14.0/clang_64/lib/QtGui.framework/QtGui\
	/Users/bhackney/Qt/5.14.0/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/bhackney/Documents/Computer\ Graphics/Computer-Graphics-work/Lab3_Starfield/build/Debug/Lab2


PostBuild.Lab2.Release:
/Users/bhackney/Documents/Computer\ Graphics/Computer-Graphics-work/Lab3_Starfield/build/Release/Lab2:\
	/Users/bhackney/Qt/5.14.0/clang_64/lib/QtOpenGL.framework/QtOpenGL\
	/Users/bhackney/Qt/5.14.0/clang_64/lib/QtWidgets.framework/QtWidgets\
	/Users/bhackney/Qt/5.14.0/clang_64/lib/QtGui.framework/QtGui\
	/Users/bhackney/Qt/5.14.0/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/bhackney/Documents/Computer\ Graphics/Computer-Graphics-work/Lab3_Starfield/build/Release/Lab2


PostBuild.Lab2.MinSizeRel:
/Users/bhackney/Documents/Computer\ Graphics/Computer-Graphics-work/Lab3_Starfield/build/MinSizeRel/Lab2:\
	/Users/bhackney/Qt/5.14.0/clang_64/lib/QtOpenGL.framework/QtOpenGL\
	/Users/bhackney/Qt/5.14.0/clang_64/lib/QtWidgets.framework/QtWidgets\
	/Users/bhackney/Qt/5.14.0/clang_64/lib/QtGui.framework/QtGui\
	/Users/bhackney/Qt/5.14.0/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/bhackney/Documents/Computer\ Graphics/Computer-Graphics-work/Lab3_Starfield/build/MinSizeRel/Lab2


PostBuild.Lab2.RelWithDebInfo:
/Users/bhackney/Documents/Computer\ Graphics/Computer-Graphics-work/Lab3_Starfield/build/RelWithDebInfo/Lab2:\
	/Users/bhackney/Qt/5.14.0/clang_64/lib/QtOpenGL.framework/QtOpenGL\
	/Users/bhackney/Qt/5.14.0/clang_64/lib/QtWidgets.framework/QtWidgets\
	/Users/bhackney/Qt/5.14.0/clang_64/lib/QtGui.framework/QtGui\
	/Users/bhackney/Qt/5.14.0/clang_64/lib/QtCore.framework/QtCore
	/bin/rm -f /Users/bhackney/Documents/Computer\ Graphics/Computer-Graphics-work/Lab3_Starfield/build/RelWithDebInfo/Lab2




# For each target create a dummy ruleso the target does not have to exist
/Users/bhackney/Qt/5.14.0/clang_64/lib/QtCore.framework/QtCore:
/Users/bhackney/Qt/5.14.0/clang_64/lib/QtGui.framework/QtGui:
/Users/bhackney/Qt/5.14.0/clang_64/lib/QtOpenGL.framework/QtOpenGL:
/Users/bhackney/Qt/5.14.0/clang_64/lib/QtWidgets.framework/QtWidgets:
