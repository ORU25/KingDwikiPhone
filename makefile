# Nama program/output dan folder bin
TARGET = KingDwikiPhone
BINDIR = bin
EXE = $(BINDIR)/$(TARGET)

# Kompiler dan flag
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iheader -Ilibs/nlohmann

# Semua file sumber (.cpp)
SRCS = $(wildcard src/*.cpp)

# Folder tempat file objek
OBJDIR = build

# Konversi src/file.cpp jadi build/file.o
OBJS = $(patsubst src/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Default: build dan jalankan program
run: $(EXE)
	$(EXE)

# Compile setiap .cpp ke .o
$(OBJDIR)/%.o: src/%.cpp
	if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build executable ke folder bin
$(EXE): $(OBJS)
	if not exist "$(BINDIR)" mkdir "$(BINDIR)"
	$(CXX) $(OBJS) -o $(EXE)

# Bersihkan file objek dan executable
clean:
	del /Q $(subst /,\,$(OBJS)) $(EXE) 2>nul || exit 0
	