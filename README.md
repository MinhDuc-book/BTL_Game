# BTL_AimGame

## Giới thiệu bản thân
Tôi tên là Nguyễn Minh Đức, sinh ra và lớn lên tại Hà Nội. Hiện nay tôi đang là sinh viên học ngành Mạng máy tính và truyền thông dữ liệu tại trường Đại học Công nghệ - Đại học Quốc gia Hà Nội.

## Mục đích của dự án
- Dự án này có tên là "AimGame" có mục đích tạo ra 1 trò chơi tập kĩ năng nhắm và sử dụng các thao tác chuột thật chính xác, có thể dùng để luyện tập cho các game cần các thao tác nhanh và chính xác
- Luyện tập kĩ năng, học hỏi các kiến thức, tư duy và kinh nghiệm trong việc thực hiện 1 dự án
- Tổ chức các file, folder một cách hợp lí để dễ dàng thay đổi, nâng cấp khi cần thiết
- Đạt được điểm số cao

## Hướng dẫn cài đặt SDL2 và các công cụ cần thiết

### 1. Cài đặt MingW
1. Tải từ trang [https://sourceforge.net/projects/mingw/](https://sourceforge.net/projects/mingw/).
2.Chạy file cài đặt và chọn 'mingw32-gcc-g++'
3. Thêm thư mục bin của MingW vào đường dẫn PATH bằng cách: Mở Setting của máy --> System --> About --> Advanced system settings --> Environment Variables --> thêm đường dẫn của thư mục bin vào PATH

### 2. Cài đặt SDL2
1. Cài đặt trình biên dịch:
    - Mở MSYS2 MSYS(màu tím)
    - Dán câu lệnh: pacman -S mingw-w64-ucrt-x86_64-gcc
    - Đợi hệ thống tự chạy rồi bấm Enter, Y
2. Cài đặt CMake:
    - Tương tư với cài đặt trình biên dịch nhưng với câu lệnh: pacman -S mingw-w64-ucrt-x86_64-cmake
3. Cài đặt SDL2:
    Sử dụng các câu lệnh sau:
    - Với SDL2 thông thường: pacman -S mingw-w64-ucrt-x86_64-SDL2
    - Thêm các phần khác:
        + Hình ảnh: mingw-w64-ucrt-x86_64-SDL2_image
        + Âm thanh (tính năng trộn âm): mingw-w64-ucrt-x86_64-SDL2_mixer
        + Âm thanh (phát lại các âm thanh từ tệp): mingw-w64-ucrt-x86_64-SDL2_sound
        + Font chữ: mingw-w64-ucrt-x86_64-SDL2_ttf 
4. Chạy chương trình
    - Ctrl + Shift + ` để mở Terminal trên VSCode
    - Gõ lệnh "make" trên Terminal
