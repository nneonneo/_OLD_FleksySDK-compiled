# quick implementation. Not particularly efficient with space

import argparse, re, codecs, random, time

parser = argparse.ArgumentParser(description='Given a text file, this will randomly sample '
                                 'sentences in the text. Outputs to stdout. The first line '
                                 'printed is the seed used')
parser.add_argument('input', help='Text file')
parser.add_argument('word_count', type=int, help='Desired word count in document')
parser.add_argument('-l', '--length', type=int, default=3, help = 'Sets the minimum number '
                    'of words in a sentence')
parser.add_argument('-s', '--seed', type=float, default=-1, help = 'Manually sets the seed')
args = parser.parse_args()

if (args.seed != -1):
    seed = args.seed
else:
    seed = time.clock()

print(seed)
random.seed(seed)
input = codecs.open(args.input, 'r', "utf-8")
text = ""
for line in input:
    text += line.strip()

sentences = re.split("\.", text)

if (len(sentences) == 0):
    exit()

totalCnt = 0
while (totalCnt <= args.word_count):
    temp = []
    for sent in sentences:
        words = re.split(" ", sent)
        rnd = random.random()
        if (len(words) >= args.length):
            try:
                if (rnd <= 0.1):
                    s = sent.strip() + "."
                    print(s)
                    totalCnt += len(words)
                    if (totalCnt > args.word_count):
                        break
                else:
                    temp.append(sent)
            except UnicodeEncodeError:
                pass
            
    sentences = list(temp)
