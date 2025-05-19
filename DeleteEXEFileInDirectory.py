
import sys
from pathlib import Path


def delete_exe_files(directory):
    try:
        # .exe 파일 목록 수집
        exe_files = list(Path(directory).rglob("*.exe"))
        
        if not exe_files:
            print("No .exe files found in the specified directory.")
            return

        # 파일 목록 출력
        print("\nFound the following .exe files:")
        for i, path in enumerate(exe_files, 1):
            print(f"{i}. {path}")

        # 사용자 확인
        print("\nDo you want to delete these all .exe files? (y/n)")
        choice = input().strip().lower()

        if choice == 'y':
            # 모두 삭제
            for path in exe_files:
                if path.is_file():
                    print(f"Deleting: {path}")
                    path.unlink()
            print("All selected .exe files have been deleted.")
        elif choice == 'n':
            print("No files were deleted.")
            return

    except PermissionError as e:
        print(f"Permission error: {e}")
    except Exception as e:
        print(f"Error accessing directory: {e}")


if __name__ == "__main__":
    directory = "."  # 기본값: 현재 디렉토리
    try:
        if len(sys.argv) > 1:
            directory = sys.argv[1]
            if not Path(directory).is_dir():
                print(f"Error: '{directory}' is not a valid directory.")
                sys.exit(1)
        delete_exe_files(directory)
    except IndexError:
        print("Error: Invalid command-line arguments.")
        print("Usage: python3 delete_exe_files.py [directory]")
        sys.exit(1)
