import os
import re
import requests
import urllib.parse


def DownVideo(VideoUrl, Cookie, Path):
    video_url = VideoUrl
    Cookie = urllib.parse.quote(Cookie, safe='…')
    headers = {
        "user-agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:121.0) Gecko/20100101 Firefox/121.0",
        "Cookie": Cookie
    }
    response = requests.get(url=video_url, headers=headers).content.decode()
    video_name = re.findall('name="title" content="(.*?)_哔哩哔哩_bilibili">', response)[0]
    print('下载中---请稍等---')
    video_link = re.findall(r'video":\[{"id":\d+,"baseUrl":"(.*?)"', response)[0]
    audio_link = re.findall(r'"audio":\[{"id":\d+,"baseUrl":"(.*?)"', response)[0]
    headers = {
        "user-agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:121.0) Gecko/20100101 Firefox/121.0",
        "referer": video_url
    }
    if Path is None or Path == 0:
        exit("path is null")
    path = Path + "/"
    print("保存路径："+path)
    video = requests.get(url=video_link, headers=headers).content
    with open(path + 'video.mp4', 'wb') as f:
        f.write(video)
    audio = requests.get(url=audio_link, headers=headers).content
    with open(path + 'audio.mp3', 'wb') as f:
        f.write(audio)

    os.system(f'ffmpeg -i "{path}video.mp4" -i "{path}audio.mp3" -c copy "{path}{video_name}.mp4"')
    os.remove(f'"{path}video.mp4"')
    os.remove(f'"{path}audio.mp3"')
