import fcntl, subprocess, json, os, sys, time, psutil
sys.path.append("..")
from bot_util import fetch
"""a file test_history.json whose content is {} is required"""
pwd = "/home/grharris/VastMlirBenchmark/autotest"

def main():
    force_mode = "-f" in sys.argv
    history_file_name = pwd + "/vast-test-cxx/test_history.json"
    result_file = open(pwd + "/tmp/msg.txt", "w")
    result_file.write("CPP EXAMPLE TEST RESULT:\n")
    trg = {"repo" : "origin",
            "branch" : "master"}
    stat = fetch.VastStatus(history_file_name, force_mode, trg, result_file)
    if stat.shouldTest:
        os.chdir(pwd + "/vast-test-cxx")
        result_file.close()
        os.system("zsh test.sh >> " + pwd + "/tmp/msg.txt")
    stat.close()

if __name__=='__main__':
    main()