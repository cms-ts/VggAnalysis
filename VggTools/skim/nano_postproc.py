#!/usr/bin/env python
import os, sys
import ROOT
ROOT.PyConfig.IgnoreCommandLineOptions = True
from PhysicsTools.NanoAODTools.postprocessing.framework.postprocessor import PostProcessor

if __name__ == "__main__":
    from optparse import OptionParser
    parser = OptionParser(usage="%prog [options] outputDir inputFiles")
    parser.add_option("-J", "--json",  dest="json", type="string", default=None, help="Select events using this JSON file")

    (options, args) = parser.parse_args()

    if len(args) < 2 :
	 parser.print_help()
         sys.exit(1)

    outdir = args[0]
    args = args[1:]

    p=PostProcessor(outdir, args, jsonInput = options.json, provenance = True)
    p.run()

