import sys,os

def combine_files(dir_name, outfile):
    if os.path.exists(dir_name) == True and os.path.isdir(dir_name) == True:
        out_fp = open(outfile, "wb")
        
        for root, dirs, files in os.walk(dir_name, topdown=False):
            for name in files:
                fp = open(os.path.join(root, name), "rb")
                out_fp.write(fp.read())
                fp.close()
                
        out_fp.close()
    else:
        print "%s dir is not exist"%dir_name
        
if __name__ == "__main__":
    helpStr = "dir output"
    if len(sys.argv) != 3:
        print "useage: %s %s"%(sys.argv[0],helpStr)
    else :
        combine_files(sys.argv[1], sys.argv[2])
        print "generate %s sucess"%(sys.argv[2])
                
