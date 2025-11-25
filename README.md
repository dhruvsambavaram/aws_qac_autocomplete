# Autocomplete with Trie

Built an autocomplete system using a trie data structure. Uses data from [AmazonQAC dataset](https://huggingface.co/datasets/amazon/AmazonQAC) - like 350M real Amazon searches. Pretty fast (millisecs to search and 0.193secs to index) and works well.

## What it does

You type a prefix, it gives you the most common words that start with it. Sorted by frequency so the popular stuff shows up first.

## Build & Run

```bash
cd src
gcc main.c trie.c -o main 2>&1
./main ../data/sorted_w2cnt_final_words.tsv
```

You can change how many results you want (default is 10):
```bash
./main ../data/sorted_w2cnt_final_words.tsv 5
```


## Example

```
$ ./main ../data/sorted_w2cnt_final_words.tsv
Loaded 525967 words into trie (indexing time: 0.189 seconds)
prefix> hall
halloween
hall
hallway
...
(search time: 0.000115 seconds)
prefix> iph
iphone
iphone case
...
(search time: 0.000122 seconds)
prefix> exit
```

Works pretty well for common prefixes. The trie makes lookups fast.
Then just type prefixes and press enter. Type `exit` to quit.

## Data Pipeline

The data comes from AmazonQAC. There's 3 scripts in `scripts/` that process it:

1. **step1_download.sh** - Downloads the AmazonQAC dataset from HuggingFace. It's huge (350M searches) so this takes a while. Saves parquet files locally.

2. **step2_extract_final_serach_term_from_data.sh** - Goes through all the parquet files and pulls out just the `final_search_term` field. Basically what people actually searched for. Outputs a TSV file.

3. **step3_split_final_search_term_to_words.sh** - Takes the search terms, splits them into individual words, counts frequencies, and filters out rare words (count < 5). Creates the final word list with counts that the trie uses.

The scripts are in `scripts/` if you want to see how it works. You need `jq`, `parquet-tools`, and basic unix stuff.

## How it works

- Loads words from TSV (word + frequency)
- Only keeps words with frequency > 10 (to save memory)
- Builds a trie - each node is a character, paths spell words
- When you type a prefix, it finds that node then collects all words in that subtree
- Sorts by frequency and returns top k

## Files

- `src/main.c` - main program, loads data and interactive loop
- `src/trie.c` - trie implementation
- `src/trie.h` - header
- `data/sorted_w2cnt_final_words.tsv` - word frequencies (already processed)
- `scripts/` - data processing scripts

The data file format is just `word<TAB>frequency` per line. Simple.
