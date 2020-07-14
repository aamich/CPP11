/*
in	input	File open for reading: the internal stream buffer supports input operations.
out *	output	File open for writing: the internal stream buffer supports output operations.
binary	binary	Operations are performed in binary mode rather than text.
ate	at end	The output position starts at the end of the file.
app	append	All output operations happen at the end of the file, appending to its existing contents.
trunc	truncate	Any contents that existed in the file before it is open are discarded.
*/

// ofstream constructor.
#include <fstream>      // std::ofstream

int main () {
  std::ofstream ofs ("test.txt", std::ofstream::out);
  ofs << "lorem ipsum";
  ofs.close();
  return 0;
}
