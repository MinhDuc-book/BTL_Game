# BTL_AimGame

## Giới thiệu bản thân
- Nguyễn Minh Đức

## Chủ đề trong game
- Đây là 1 trò chơi tập kĩ năng sử dụng các thao tác chuột, phím thật nhanh và chính xác

## Ngưỡng điểm ước lượng: 8.5 điểm

## Lý do bảo vệ ngưỡng điểm:
- Học, làm game và nộp lên Github đều đặn
- Áp dụng được các kiến thức đã học vào game như: class, chia tách file,...
- Có âm thanh, hình ảnh, văn bản
- Game tự nghĩ ra bằng việc kết hợp nhiều game từng chơi

## Hướng dẫn cài đặt SDL2 và các công cụ cần thiết

### 1. Cài đặt MingW
1. Tải từ trang [https://sourceforge.net/projects/mingw/](https://sourceforge.net/projects/mingw/).

2. Chạy file cài đặt và chọn 'mingw32-gcc-g++'.

3. Thêm thư mục bin của MingW vào đường dẫn PATH bằng cách: Mở Setting của máy --> System --> About --> Advanced system settings --> Environment Variables --> thêm đường dẫn của thư mục bin vào PATH.

### 2. Cài đặt SDL2

**1. Cài đặt trình biên dịch:**
- Mở MSYS2 MSYS
    
- Dán câu lệnh: ```pacman -S mingw-w64-ucrt-x86_64-gcc```

- Đợi hệ thống tự chạy rồi bấm Enter, Y

**2. Cài đặt CMake:**
- Tương tự với cài đặt trình biên dịch nhưng với câu lệnh: ```pacman -S mingw-w64-ucrt-x86_64-cmake```

**3. Cài đặt SDL2:**
Sử dụng các câu lệnh sau:
- Với SDL2 thông thường:  ```pacman -S mingw-w64-ucrt-x86_64-SDL2```

- Thêm các phần khác:
    + Hình ảnh: ```mingw-w64-ucrt-x86_64-SDL2_image```

    + Âm thanh (tính năng trộn âm): ```mingw-w64-ucrt-x86_64-SDL2_mixer```

    + Âm thanh (phát lại các âm thanh từ tệp): ```mingw-w64-ucrt-x86_64-SDL2_sound```

    + Font chữ: ```mingw-w64-ucrt-x86_64-SDL2_ttf```

- Chi tiết hơn: [SDL2 cho VSCode](https://phdoanh.github.io/doanhanma/materials/sdl2-for-vscode).
     
**4. Chạy chương trình:**
- Ctrl + Shift + ` để mở Terminal trên VSCode

- Gõ lệnh ```make``` trên Terminal để chạy chương trình (vì đã đổi tên file "mingw32-make.exe" thành "make.exe")
