import subprocess
from multiprocessing import Pool
import datetime

# subprocess.run(["ls", "-l"]) 
def run_command(command):
    now = datetime.datetime.now()
    print(command)
    with open(f"out/out_cmd_{command.replace(' ', '-').replace('./', '').replace('/', '--')}.txt", "a") as f:
        subprocess.call(command, shell=True, stdout=f, stderr=f)
    print(f"{command}, time: {datetime.datetime.now() - now}")


if __name__ == '__main__':
    # start 4 worker processes
    PROGRAM = "./emili"
    INSTANCES_DIR = "/home/tagotuga/Emili-MDVRP-extension/instances/"
    
    instance_names = open("/home/tagotuga/Emili-MDVRP-extension/instances/instancenames.txt").readlines()
    instance_names = [name.split()[0] for name in instance_names]

    test_commands = []

    for name in instance_names:
        test_commands.extend([
            f"{PROGRAM} {INSTANCES_DIR}{name}.txt MDVRP 4 fils vnd first cw locmin 2opt 2opt* exchange move iteration rndmv exchange 5 test 100 -it 1200 rnds 0",
        ])
        test_commands.extend([
            f"{PROGRAM} {INSTANCES_DIR}{name}.txt MDVRP 4 fils vnd first cw locmin 2opt 2opt* exchange move iteration rndmv exchange 5 test 100 -it 1200 rnds 1",
        ])
        test_commands.extend([
            f"{PROGRAM} {INSTANCES_DIR}{name}.txt MDVRP 4 fils vnd first cw locmin 2opt 2opt* exchange move iterations 100 rndmv exchange 5 test 100 -it 1200 rnds 2",
        ])
        #test_commands.extend([
        #    f"{PROGRAM} {INSTANCES_DIR}{name}.txt MDVRP 3 fils vnd first cw locmin 2opt 2opt* exchange2 exchange move iteration rndmv exchange 5 test 100 -it 1200 rnds 3",
        #])
        #test_commands.extend([
        #    f"{PROGRAM} {INSTANCES_DIR}{name}.txt MDVRP 3 fils vnd first cw locmin 2opt 2opt* exchange2 exchange move iteration rndmv exchange 5 test 100 -it 1200 rnds 4",
        #]) 
        test_commands.extend([
            f"{PROGRAM} {INSTANCES_DIR}{name}.txt MDVRP 4 fils vnd first cw locmin 2opt 2opt* exchange move iterations 100 rndmv exchange 5 test 100 -it 1200 rnds 6",
        ])
        #test_commands.extend([
        #    f"{PROGRAM} {INSTANCES_DIR}{name}.txt MDVRP 3 fils vnd first cw locmin 2opt 2opt* exchange2 exchange move iteration rndmv exchange 5 test 100 -it 1200 rnds 7",
        #])
        #test_commands.extend([
        #    f"{PROGRAM} {INSTANCES_DIR}{name}.txt MDVRP 3 fils vnd first cw locmin 2opt 2opt* exchange2 exchange move iteration rndmv exchange 5 test 100 -it 1200 rnds 9",
        #])
        #test_commands.extend([
        #    f"{PROGRAM} {INSTANCES_DIR}{name}.txt MDVRP 3 fils vnd first cw locmin 2opt 2opt* exchange2 exchange move iteration rndmv exchange 5 test 100 -it 1200 rnds 10",
        #])
        #test_commands.extend([
        #    f"{PROGRAM} {INSTANCES_DIR}{name}.txt MDVRP 3 fils vnd first cw locmin 2opt 2opt* exchange2 exchange move iteration rndmv exchange 5 test 100 -it 1200 rnds 12",
        #])
    
    now = datetime.datetime.now()
    # print(test_commands)
    with Pool(processes=3) as pool:
        pool.map(run_command, test_commands, chunksize=1)
    print(f"done, time: {datetime.datetime.now() - now}")