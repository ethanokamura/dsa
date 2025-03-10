/**
 * @author Ethan Okamura (eokamura)
 * @email: eokamura@ucsc.edu
 * @file Shuffle.cpp
 * @brief Performs a perfect shuffle using the List ADT
 */

#include <iomanip>

#include "List.h"

// O(n)
void shuffle(List& D) {
  List first;
  int mid = D.length() / 2;
  // split
  D.moveFront();
  for (int i = 0; i < mid; i++) {
    first.insertBefore(D.peekNext());
    D.eraseAfter();
  }
  // merge
  first.moveFront();
  for (int i = 0; i < mid; i++) {
    D.moveNext();
    D.insertAfter(first.peekNext());
    D.moveNext();
    first.eraseAfter();
  }
}

// O(n * nPi)
int getShuffleCount(List& D, int i) {
  int count{};
  D.insertBefore(i);
  if (i < 2) return i + 1;
  List shuffled_deck = D;
  // O(n)
  shuffle(shuffled_deck);
  count++;
  // O(nPi)
  while (!(shuffled_deck == D)) {
    // O(n)
    shuffle(shuffled_deck);
    count++;
  }
  return count;
}

int main(int argc, char** argv) {
  if (argc != 2) return -1;
  int deck_size = std::stoi(argv[1]);
  List deck;
  std::cout << std::left << std::setw(16) << "deck size"
            << "shuffle count" << std::endl;
  for (int i = 0; i < 30; i++) std::cout << '-';
  std::cout << '\n';
  // O(n)
  for (int i = 0; i < deck_size; i++) {
    int count = getShuffleCount(deck, i);
    std::cout << ' ' << std::left << std::setw(16) << i + 1 << count << '\n';
  }
  return 0;
}