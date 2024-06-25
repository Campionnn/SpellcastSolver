Solves Discord Spellcast activity\
Creates a trie for all possible words then a trie for all valid answers possible from the given grid and bonuses\
Scores every valid word then sorts them and returns along with the correct path to achieve the score\
Does not calculate for swaps

## Building
For use with [SpellcastReader](https://github.com/Campionnn/SpellcastReader) requires [pybind11](https://pybind11.readthedocs.io/en/stable/installing.html) and run the cmake file
