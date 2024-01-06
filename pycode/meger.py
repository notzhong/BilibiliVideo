import os
import re
import requests
import urllib.parse


def ReadUrl() -> [str]:
    url_list = [str]
    with open('https.file', 'r', encoding='utf-8') as file:
        line = file.readline()
        while line:
            url_list.append(line)
            line = file.readline()
    return url_list


def DownVideo(Path, Cookie=""):
    Url_list = ReadUrl()
    cookie = Cookie
    if Cookie:
        cookie = urllib.parse.quote(Cookie, safe='…')
    # for video_url in Url_list:
    #     print(video_url)
    # print(Cookie)
    # exit(1000)

    headers = {
        "user-agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:121.0) Gecko/20100101 Firefox/121.0",
        "Cookie": cookie
    }

    for video_url in Url_list[1:]:
        video_url = video_url.replace('\n', '')
        response = requests.get(url=video_url, headers=headers).content.decode()
        video_name = re.findall('name="title" content="(.*?)_哔哩哔哩_bilibili">', response)[0]
        print('下载中---请稍等---')
        video_link = re.findall(r'video":\[{"id":\d+,"baseUrl":"(.*?)"', response)[0]
        audio_link = re.findall(r'"audio":\[{"id":\d+,"baseUrl":"(.*?)"', response)[0]
        headers = {
            "user-agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:121.0) Gecko/20100101 Firefox/121.0",
            "referer": video_url,
            "Cookie": cookie
        }
        if Path is None or Path == 0:
            exit("path is null")
        path = Path + "/"
        video = requests.get(url=video_link, headers=headers).content
        with open(path + 'video.mp4', 'wb') as f:
            f.write(video)
        audio = requests.get(url=audio_link, headers=headers).content
        with open(path + 'audio.mp3', 'wb') as f:
            f.write(audio)

        os.system(f'ffmpeg -i "{path}video.mp4" -i "{path}audio.mp3" -c copy "{path}{video_name}.mp4" >> null')
        os.remove(f"{path}video.mp4")
        os.remove(f"{path}audio.mp3")
        print(video_name + ' 下载完成！！！')
