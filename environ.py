#!/usr/bin/env python2

import platform, datetime, sys
from subprocess import Popen, PIPE

print r"\newcommand{\platform}{%s}" % platform.platform().replace('_', '\_')
print r"\newcommand{\xetexver}{%s}" % Popen(['xelatex', '--version'], stdout=PIPE).stdout.read().split('\n')[0]
print r"\newcommand{\pythonver}{%s}" % (sys.subversion[0] + ' ' + sys.version.split()[0])
print r"\newcommand{\buildtime}{%s}" % str(datetime.datetime.now())
buildno = int(open("BUILD").read())
print r"\newcommand{\buildno}{%04d}" % buildno
open("BUILD", "w").write(str(buildno + 1))

