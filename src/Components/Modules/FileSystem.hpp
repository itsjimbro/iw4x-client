namespace Components
{
	class FileSystem : public Component
	{
	public:
		class AbstractFile
		{
		public:
			virtual ~AbstractFile() {};

			virtual bool exists() = 0;
			virtual std::string getName() = 0;
			virtual std::string& getBuffer() = 0;
		};

		class File : public AbstractFile
		{
		public:
			File() {};
			File(std::string file) : filePath(file) { this->read(); };

			bool exists() { return !this->buffer.empty(); };
			std::string getName() { return this->filePath; };
			std::string& getBuffer() { return this->buffer; };

		private:
			std::string filePath;
			std::string buffer;

			void read();
		};

		class RawFile : public AbstractFile
		{
		public:
			RawFile() {};
			RawFile(std::string file) : filePath(file) { this->read(); };

			bool exists() { return !this->buffer.empty(); };
			std::string getName() { return this->filePath; };
			std::string& getBuffer() { return this->buffer; };

		private:
			std::string filePath;
			std::string buffer;

			void read();
		};

		class FileReader
		{
		public:
			FileReader() : size(-1), name(), handle(0) {};
			FileReader(std::string file);
			~FileReader();

			bool exists();
			std::string getName();
			std::string getBuffer();
			int getSize();
			bool read(void* buffer, size_t size);
			void seek(int offset, int origin);

		private:
			int handle;
			int size;
			std::string name;
		};

		class FileWriter
		{
		public:
			FileWriter(std::string file, bool append = false) : filePath(file), handle(0) { this->open(append); };
			~FileWriter() { this->close(); };

			void write(std::string data);

		private:
			int handle;
			std::string filePath;

			void open(bool append = false);
			void close();
		};

		FileSystem();
		~FileSystem();

#if defined(DEBUG) || defined(FORCE_UNIT_TESTS)
		const char* getName() { return "FileSystem"; };
#endif

		static std::vector<std::string> GetFileList(std::string path, std::string extension);
		static std::vector<std::string> GetSysFileList(std::string path, std::string extension, bool folders = false);
		static void DeleteFile(std::string folder, std::string file);

	private:
		static std::mutex Mutex;
		static std::recursive_mutex FSMutex;
		static Utils::Memory::Allocator MemAllocator;

		static int ReadFile(const char* path, char** buffer);
		static char* AllocateFile(int size);
		static void FreeFile(void* buffer);

		static void RegisterFolder(const char* folder);

		static void RegisterFolders();
		static void StartupStub();
		static int ExecIsFSStub(const char* execFilename);

		static void FsStartupSync(const char* a1);
		static void FsRestartSync(int a1, int a2);
		static void DelayLoadImagesSync();
		static int LoadTextureSync(Game::GfxImageLoadDef **loadDef, Game::GfxImage *image);
	};
}
