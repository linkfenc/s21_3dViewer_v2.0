#include "parser_file.h"

namespace s21 {

void ParserFile::parseFile(const std::string &fileName, data &data) {
  std::ifstream file;
  std::string line;
  file.open(fileName);
  while (getline(file, line)) {
    if (line.front() == 'v' && line[1] == ' ')
      parseVertex(line.substr(1, line.size()), data);
    if (line.front() == 'f' && line[1] == ' ')
      parseFacet(line.substr(1, line.size()), data);
  }
  data.matrix_3d.setCols(3);
  data.matrix_3d.setRows(data.count_of_vertexes);
  Normalize(data);
  file.close();
}

void ParserFile::parseVertex(const std::string &line, data &data) {
  std::stringstream str(line);
  std::string token;
  for (int i = 0; str >> token && i != 3; ++i) {
    double var = std::stod(token);
    if (fabs(var) > data.max_d) data.max_d = fabs(var);
    data.matrix_3d.insert(var);
  }
  data.count_of_vertexes++;
}

void ParserFile::parseFacet(const std::string &line, data &data) {
  std::stringstream str(line);
  std::string first_token;
  std::string token;
  for (int i = 0; str >> token; ++i) {
    if (i != 0)
      data.polygons.push_back(std::stod(token) - 1);
    else
      first_token = token;
    data.polygons.push_back(std::stod(token) - 1);
  }
  data.polygons.push_back(std::stod(first_token) - 1);
  data.count_of_facets++;
}

void ParserFile::Normalize(data &d) {
  if (d.max_d > 1) {
    for (size_t i = 0; i != d.count_of_vertexes; ++i) {
      d.matrix_3d(i, 0) /= d.max_d;
      d.matrix_3d(i, 1) /= d.max_d;
      d.matrix_3d(i, 2) /= d.max_d;
    }
  }
}

}  // namespace s21
