import subprocess

if __name__ == "__main__":
    max_scores = []
    test_names = ["kittens.in.txt",  "me_at_the_zoo.in", "trending_today.in", "videos_worth_spreading.in"]
    with open("max_score.txt", "r") as fin:
        for filename in test_names:
            filename, score = fin.readline().split()
            score = int(score)
            cat = subprocess.Popen(('cat', "tests/" + filename), stdout=subprocess.PIPE)
            output = subprocess.check_output(("./solve"), stdin=cat.stdout).decode()
            cat.wait()
            print("Filename:", filename)
            print(output)
            print(output.split())
            max_scores.append(max(score, int(output.split()[-1])))
    print("New total score:", sum(max_scores))
    with open("max_score.txt", "w") as fout:
        for score, filename in zip(max_scores, test_names):
            fout.write("{} {}\n".format(filename, score))

        fout.write("Summarize: {}\n".format(sum(max_scores)))
            
