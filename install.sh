#!/bin/sh

OS_NAME="$(cmake -P ./PrintOS.cmake 2>&1)"
PROJECT_NAME="SimpleSearchEngine"
SECOND_TARGET="SimpleSearchEngineIndexer"
CMAKE_BUILD_DIR="$HOME/CMakeBuilds"
CMAKE_PROJECT_DIR="$CMAKE_BUILD_DIR/$PROJECT_NAME"

if [ "x$SAVE_PREV" = "x" ]; then
  if [ -e "$CMAKE_PROJECT_DIR" ]; then
    rm -rf "$CMAKE_PROJECT_DIR"
  fi
fi

EXEC_EXTENSION=".exe"
EXEC_PATH="$CMAKE_PROJECT_DIR/bin/$PROJECT_NAME$EXEC_EXTENSION"
SECOND_EXEC_PATH="$CMAKE_PROJECT_DIR/bin/$SECOND_TARGET$EXEC_EXTENSION"

if [ "$OS_NAME" = "Linux" ]; then
  EXEC_EXTENSION=".run"
  EXEC_PATH="$CMAKE_PROJECT_DIR/bin/$PROJECT_NAME"
  SECOND_EXEC_PATH="$CMAKE_PROJECT_DIR/bin/$SECOND_TARGET"
elif [ "$OS_NAME" = "MacOS" ]; then
  EXEC_EXTENSION=".run"
  EXEC_PATH="$CMAKE_PROJECT_DIR/bin/$PROJECT_NAME"
  SECOND_EXEC_PATH="$CMAKE_PROJECT_DIR/bin/$SECOND_TARGET"
fi

EXEC_LINK_PATH="$HOME/$PROJECT_NAME$EXEC_EXTENSION"
SECOND_EXEC_LINK_PATH="$HOME/$SECOND_TARGET$EXEC_EXTENSION"

if (cmake -S . -B "$CMAKE_PROJECT_DIR" -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" && cmake --build "$CMAKE_PROJECT_DIR" --target "$PROJECT_NAME" "$SECOND_TARGET"); then
  rm -f "$EXEC_LINK_PATH"
  rm -f "$SECOND_EXEC_LINK_PATH"
  ln -s "$EXEC_PATH" "$EXEC_LINK_PATH"
  ln -s "$SECOND_EXEC_PATH" "$SECOND_EXEC_LINK_PATH"
  echo ''

  if ("$EXEC_LINK_PATH" -h >/dev/null 2>/dev/null && "$SECOND_EXEC_LINK_PATH" -h >/dev/null 2>/dev/null); then
    echo "Congratulations! $PROJECT_NAME was compiled successfully."
    echo ''
    "$EXEC_LINK_PATH" -h
    echo ''
    "$SECOND_EXEC_LINK_PATH" -h
    echo ''

    if [ "$OS_NAME" = "Linux" ]; then
      printf 'Do you want to add this utility to /usr/bin (y/n)? ' && read -r CHOISE
      COMMON_LINK_PATH="/usr/bin/${PROJECT_NAME:?}"
      COMMON_SECOND_LINK_PATH="/usr/bin/${SECOND_TARGET:?}"
      COMMON_PROJECT_DIR="/opt/${PROJECT_NAME:?}"
      COMMON_EXEC_PATH="$COMMON_PROJECT_DIR/bin/$PROJECT_NAME"
      COMMON_SECOND_EXEC_PATH="$COMMON_PROJECT_DIR/bin/$SECOND_TARGET"

      if [ "$CHOISE" = "y" ]; then
        sudo -S rm -f "$COMMON_LINK_PATH"
        sudo rm -f "$COMMON_SECOND_LINK_PATH"

        if (sudo ln -s "$EXEC_PATH" "$COMMON_LINK_PATH"); then
          if [ -e "$COMMON_PROJECT_DIR" ]; then
            sudo rm -rf "$COMMON_PROJECT_DIR"
          fi

          sudo rm -f "$COMMON_LINK_PATH"
          sudo cp -r "$CMAKE_PROJECT_DIR" "$COMMON_PROJECT_DIR"
          sudo ln -s "$COMMON_EXEC_PATH" "$COMMON_LINK_PATH"
          sudo ln -s "$COMMON_SECOND_EXEC_PATH" "$COMMON_SECOND_LINK_PATH"
          echo "Accepted, run utility with $PROJECT_NAME and $SECOND_TARGET"
        else
          echo 'Please try again later.'
          echo "Declined, run utility with $EXEC_LINK_PATH and $SECOND_EXEC_LINK_PATH"
        fi
      else
        echo "Declined, run utility with $EXEC_LINK_PATH and $SECOND_EXEC_LINK_PATH"
      fi
    else
      echo "Run utility with $EXEC_LINK_PATH and $SECOND_EXEC_LINK_PATH"
    fi
    exit 0
  elif (cd "$CMAKE_PROJECT_DIR" && "./$PROJECT_NAME$EXEC_EXTENSION" -h >/dev/null 2>/dev/null); then
    rm -f "$EXEC_LINK_PATH"
    rm -f "$SECOND_EXEC_LINK_PATH"
    rm -rf "$HOME/${PROJECT_NAME:?}"
    echo "Congratulations! $PROJECT_NAME was compiled successfully."
    echo "Because of Windows-specific limitations, it is not possible to create a link to it."
    echo "You can run it from $HOME/$PROJECT_NAME as .\\$PROJECT_NAME$EXEC_EXTENSION and  .\\$SECOND_TARGET$EXEC_EXTENSION"
    echo "Or you can run CMD.EXE with administrative privileges and type: "
    echo 'mklink "%userprofile%\SimpleSearchEngine.exe" "%userprofile%\SimpleSearchEngine\SimpleSearchEngine.exe"'
    echo 'mklink "%userprofile%\SimpleSearchEngineIndexer.exe" "%userprofile%\SimpleSearchEngine\SimpleSearchEngineIndexer.exe"'
    echo ''
    mkdir "$HOME/$PROJECT_NAME"
    cp "$CMAKE_PROJECT_DIR/$PROJECT_NAME$EXEC_EXTENSION" "$HOME/$PROJECT_NAME/$PROJECT_NAME$EXEC_EXTENSION"
    cp "$CMAKE_PROJECT_DIR/$SECOND_TARGET$EXEC_EXTENSION" "$HOME/$PROJECT_NAME/$SECOND_TARGET$EXEC_EXTENSION"
    cd "$HOME/$PROJECT_NAME" && "./$PROJECT_NAME$EXEC_EXTENSION" -h && "./$SECOND_TARGET$EXEC_EXTENSION" -h
    exit 0
  else
    echo 'Oops! Could not execute the program.'
    exit 1
  fi
else
  echo 'Error occurred during running CMake. Make sure that it is installed and configured properly.'
  exit 1
fi
