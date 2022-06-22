1. config file に実装しなければならない項目

- port and host each server
  サーバーを複数設定できるようにする？
  host は ip アドレスと解釈もできる
  hosts ファイルで ip アドレスがローカルではなくてもアクセスできるようにすればよい？
- server names or not
  nginx の場合は、サーバー名=host 名のような扱いをうけていた
  基本的にリクエストヘッダを読み取って server_name が一致しなかった場合、リクエストを弾く仕組みにするらしい
- default error page
- limit client body size
  ここで動的に確保するべき recv のバッファサイズが来まる
- routing の設定
  - http method
  - リダイレクト
  - routing のネスト
  - Turn on or off directory listing よくわからん
- リクエストがディレクトリだったときに返す、default file
- CGI 実行ファイルの拡張子
- uploaded file のルーティング

QWN	Q	
config fileの構造はcub3dの要素みたいな感じにする
空白が一つ以上だった場合許容しないようにする

要素 空白 要素

