#!/usr/bin/env python2

import platform, datetime


print r"\newcommand{\platform}{%s}" % platform.platform().replace('_', '\_')
print r"\newcommand{\pythonver}{%s}" % platform.python_version()
print r"\newcommand{\buildtime}{%s}" % str(datetime.datetime.now())
buildno = int(open("BUILD").read())
print r"\newcommand{\buildno}{%04d}" % buildno
open("BUILD", "w").write(str(buildno + 1))

