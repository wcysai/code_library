#!/usr/bin/env python2
import re, os, hashlib, yaml

line_count = 1

scl = yaml.load(open("scl.yaml").read())

LANGS = {"c": "C", "cpp": "C++", "py": "Python", "pl": "Perl",
     "sh": "sh", "java": "Java"}

def lang(ext):
    if not ext: return "{}"
    ext = ext.lower()
    return LANGS[ext] if ext in LANGS else "{}"

def gen_section(sect_yaml):
    global line_count

    name = sect_yaml['name']
    dirname = sect_yaml['dir']
    files = sect_yaml['files']

    sect = []
    sect.append("\\section{%s}" % name)

    subsects = []
    for (idx, f) in enumerate(files):
        title = f['title']
        fname = f['fname']
        desc = f.get('desc', None)
        usage = f.get('usage', None)
        tcmplx = f.get('time', None)

        with open("src/%s/%s" % (dirname, fname), "r") as fp:
            code = fp.read()

        extension = fname.split('.')[-1]
    
        sect.append("\\subsection{%s}" % title)
    
        if extension == 'tex' : 
            sect.append(code)
            continue

        def digest_line(s):
            return hashlib.md5(re.sub(r'\s|//.*', '', s).encode('utf8')).hexdigest()[-4:]

        for line in code.split("\n"):
            sect.append("\\createlinenumber{%d}{%s}" % (line_count, digest_line(line)))
            line_count += 1
        
        descriptions = []
        
        if desc:
            descriptions.append(desc.strip())
            descriptions.append('\\par')
        
        if usage:
            descriptions.append('\\textbf{Usage:}\\par') 
            descriptions.append('\\begin{tabular}{p{4cm} p{9cm}}')
            for (funct, descript) in usage.items() :
                descriptions.append('\lstinline|%s| & %s \\\\' % (funct, descript))
            descriptions.append('\\end{tabular}')

        if tcmplx:      # print time complexity
            descriptions.append('\\textbf{Time Complexity:}')
            descriptions.append(tcmplx.strip())
            descriptions.append('\\par')
        
        if descriptions :
            sect.append('\\begin{mdframed}[hidealllines=true,backgroundcolor=blue!5]')
            sect.append('\n'.join(descriptions))
            sect.append('\\end{mdframed}\\vspace{-10pt}')
        
        sect.append("\\begin{lstlisting}[language=%s]" % lang(extension))
        sect.append(code.decode('utf-8'))
        sect.append("\\end{lstlisting}")

    return "\n".join(sect).encode('utf-8')

for section in scl:
  print gen_section(section)
