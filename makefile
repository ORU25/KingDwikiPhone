TARGET = KingDwikiPhone

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iheader -Ilibs/nlohmann

# Semua file sumber (.cpp)
SRCS = $(wildcard src/*.cpp)

# Folder tempat file objek
OBJDIR = build

# Konversi src/file.cpp jadi build/file.o
OBJS = $(patsubst src/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Rule buat compile setiap src/%.cpp ke build/%.o
$(OBJDIR)/%.o: src/%.cpp
	if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target utama link dari semua file objek
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

clean:
	del /Q $(subst /,\,$(OBJS)) $(TARGET) 2>nul || exit 0
