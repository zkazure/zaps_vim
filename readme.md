[package]
name = "pixel-vim"
version = "0.1.0"
edition = "2021"

[dependencies]
winapi = { version = "0.3", features = ["winuser", "processthreadsapi", "libloaderapi"] }
anyhow = "1.0"        # 错误处理
log = "0.4"           # 日志
env_logger = "0.10"   # 日志实现