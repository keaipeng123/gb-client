#!/usr/bin/env python3
"""简易 TCP 测试服务端 — 用于验证客户端断线重连"""
import socket
import sys

HOST = "0.0.0.0"
PORT = 12345

def main():
    while True:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind((HOST, PORT))
        s.listen(1)
        print(f"[服务端] 监听 {HOST}:{PORT}，等待客户端连接...")
        conn, addr = s.accept()
        print(f"[服务端] 客户端已连接: {addr}")
        try:
            while True:
                data = conn.recv(1024)
                if not data:
                    print("[服务端] 客户端断开连接")
                    break
                print(f"[服务端] 收到 {len(data)} 字节: {data.hex()} -> {data!r}")
        except ConnectionResetError:
            print("[服务端] 连接被重置")
        finally:
            conn.close()
            s.close()

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n[服务端] 退出")
        sys.exit(0)
