# IPTV Client for linux

Written in c++ 20, along with gtkmm-4.0
<br>
Majority of dependencies are handled via meson wrap


## Format compatibility
This application is written with this format in mind:
```
#EXTM3U
#EXTINF:-1 tvg-id="news1.us" tvg-name="News Channel 1" tvg-logo="http://example.com/logos/news1.png" group-title="News",News Channel 1
http://example-provider.com:8080/live/user123/pass456/10001.ts

#EXTINF:-1 tvg-id="sports1.us" tvg-name="Sports HD" tvg-logo="http://example.com/logos/sports1.png" group-title="Sports",Sports HD
http://example-provider.com:8080/live/user123/pass456/10002.ts

#EXTINF:-1 tvg-id="movies1.us" tvg-name="Movie Channel" tvg-logo="http://example.com/logos/movies1.png" group-title="Movies",Movie Channel
http://example-provider.com:8080/live/user123/pass456/10003.ts

#EXTINF:-1 tvg-id="doc1.us" tvg-name="Discovery Plus" tvg-logo="http://example.com/logos/doc1.png" group-title="Documentary",Discovery Plus
http://example-provider.com:8080/live/user123/pass456/10005.ts

#EXTINF:-1 tvg-id="" tvg-name="Example Series S01 E01" tvg-logo="http://example.com/posters/nebula-drift.jpg" group-title="Series - Sci-Fi",Example Series S01 E01
http://example-provider.com:8080/series/user123/pass456/60001.mkv

#EXTINF:-1 tvg-id="" tvg-name="Example Series S01 E02" tvg-logo="http://example.com/posters/nebula-drift.jpg" group-title="Series - Sci-Fi",Example Series S01 E02
http://example-provider.com:8080/series/user123/pass456/60002.mkv

#EXTINF:-1 tvg-id="" tvg-name="Example Series S01 E03" tvg-logo="http://example.com/posters/nebula-drift.jpg" group-title="Series - Sci-Fi",Example Series S01 E03
http://example-provider.com:8080/series/user123/pass456/60003.mkv

#EXTINF:-1 tvg-id="" tvg-name="Example Series S02 E01" tvg-logo="http://example.com/posters/nebula-drift.jpg" group-title="Series - Sci-Fi",Example Series S02 E01
http://example-provider.com:8080/series/user123/pass456/60004.mkv

#EXTINF:-1 tvg-id="" tvg-name="Example Series S02 E02" tvg-logo="http://example.com/posters/nebula-drift.jpg" group-title="Series - Sci-Fi",Example Series S02 E02
http://example-provider.com:8080/series/user123/pass456/60005.mkv

#EXTINF:-1 tvg-id="" tvg-name="Test Series S01 E01" tvg-logo="http://example.com/posters/cold-harbor.jpg" group-title="Series - Drama",Test Series S01 E01
http://example-provider.com:8080/series/user123/pass456/61001.mkv

#EXTINF:-1 tvg-id="" tvg-name="Test Series S01 E02" tvg-logo="http://example.com/posters/cold-harbor.jpg" group-title="Series - Drama",Test Series S01 E02
http://example-provider.com:8080/series/user123/pass456/61002.mkv

#EXTINF:-1 tvg-id="" tvg-name="Test Series S01 E03" tvg-logo="http://example.com/posters/cold-harbor.jpg" group-title="Series - Drama",Test Series S01 E03
http://example-provider.com:8080/series/user123/pass456/61003.mkv

#EXTINF:-1 tvg-id="" tvg-name="Test Series S01 E04" tvg-logo="http://example.com/posters/cold-harbor.jpg" group-title="Series - Drama",Test Series S01 E04
http://example-provider.com:8080/series/user123/pass456/61004.mkv

#EXTINF:-1 tvg-id="" tvg-name="Laugh Track S01 E01" tvg-logo="http://example.com/posters/laugh-track.jpg" group-title="Series - Comedy",Laugh Track S01 E01
http://example-provider.com:8080/series/user123/pass456/62001.mkv

#EXTINF:-1 tvg-id="" tvg-name="Laugh Track S01 E02" tvg-logo="http://example.com/posters/laugh-track.jpg" group-title="Series - Comedy",Laugh Track S01 E02
http://example-provider.com:8080/series/user123/pass456/62002.mkv

#EXTINF:-1 tvg-id="" tvg-name="Laugh Track S03 E10" tvg-logo="http://example.com/posters/laugh-track.jpg" group-title="Series - Comedy",Laugh Track S03 E10
http://example-provider.com:8080/series/user123/pass456/62003.mkv

```