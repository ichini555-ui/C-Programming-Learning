# C Device Monitoring System

C言語で開発した簡易的なデバイス監視システムです。

複数のセンサーを想定した温度データを処理し、温度に応じてセンサーの状態を NORMAL、WARNING、CRITICAL に判定します。

C言語の基本文法だけでなく、組み込み開発でも使用される `struct`、`enum`、ポインタ、配列、関数などを実践的に学習することを目的として開発しました。

## 概要

センサーごとに以下の情報を管理します。

* センサーID
* 温度
* センサー状態

温度の値に応じて、センサーの状態を自動的に判定します。

## 主な機能

* センサー情報の構造体管理
* 温度データの正規化
* 温度による状態判定
* 最大温度の取得
* センサー状態の集計
* 監視結果の表示
* 監視結果のサマリー表示

## 温度判定

温度のしきい値（Threshold）を以下のように設定しています。

| 温度        | 状態         |
| --------- | ---------- |
| 40未満      | `NORMAL`   |
| 40以上 60未満 | `WARNING`  |
| 60以上      | `CRITICAL` |

### 使用している定数

```c
const int CRITICAL_THRESHOLD = 60;
const int WARNING_THRESHOLD = 40;
```

## センサー情報の管理

センサー情報は `struct Sensor` を使用して管理しています。

```c
struct Sensor {
    int id;
    int temperature;
    enum SensorStatus status;
};
```

これにより、センサーID、温度、状態を1つのデータとしてまとめて管理しています。

また、センサーの状態には `enum` を使用しています。

```c
enum SensorStatus {
    NORMAL,
    WARNING,
    CRITICAL
};
```

## プログラムの処理フロー

プログラムは以下の流れで処理します。

1. センサー情報を配列として初期化
2. 温度データを正規化
3. 最大温度を取得
4. 各センサーの温度を判定
5. センサーの状態を更新
6. `NORMAL`、`WARNING`、`CRITICAL` の件数を集計
7. 監視結果をサマリーとして表示
8. 各センサーの最終状態を表示

## 主な関数

### `check_temperature()`

温度を確認し、センサーの状態を判定します。

```c
enum SensorStatus check_temperature(int temperature)
```

### `normalize_sensors()`

負の温度値を `0` に補正します。

```c
void normalize_sensors(struct Sensor *sensors, int size)
```

### `find_max_sensor_temperature()`

センサーの中から最大温度を取得します。

```c
int find_max_sensor_temperature(struct Sensor *sensors, int size)
```

### `monitor_sensors()`

各センサーの温度を確認し、状態を更新します。

```c
void monitor_sensors(struct Sensor *sensors, int size)
```

### `count_sensor_statuses()`

センサーの状態ごとの件数を集計します。

```c
void count_sensor_statuses(
    int *normal_count,
    int *warning_count,
    int *critical_count,
    struct Sensor *sensors,
    int size
)
```

ポインタを使用して、集計結果を呼び出し元へ返しています。

### `print_summary()`

監視結果のサマリーを表示します。

## 使用技術

* C
* GCC
* Visual Studio Code
* MSYS2 / UCRT64
* Standard C Library

## コンパイル方法

```bash
gcc device_monitor.c -o device_monitor
```

## 実行方法

```bash
./device_monitor.exe
```

## 実行結果

```text
Max temperature: 65
Temperature: 0
Sensor 1: NORMAL

Temperature: 50
Sensor 2: WARNING

Temperature: 65
Sensor 3: CRITICAL

Temperature: 33
Sensor 4: NORMAL

Temperature: 15
Sensor 5: NORMAL

=== DEVICE MONITOR SUMMARY ===

Max temperature: 65
Normal sensors: 3
Warning sensors: 1
Critical sensors: 1
===============================

Sensor 1: Temperature 0, Status NORMAL
Sensor 2: Temperature 50, Status WARNING
Sensor 3: Temperature 65, Status CRITICAL
Sensor 4: Temperature 33, Status NORMAL
Sensor 5: Temperature 15, Status NORMAL
```

## 学習したC言語の技術

このプロジェクトでは、以下のC言語の技術を使用しました。

* 変数
* 配列
* `for` 文
* `if / else` 文
* 関数
* ポインタ
* 構造体（`struct`）
* 列挙型（`enum`）
* 定数
* 戻り値
* `const char *`
* 構造体配列
* センサーデータの処理・集計

## 開発を通して学んだこと

このプロジェクトを通して、C言語でデータを構造化し、複数の関数に処理を分けてプログラムを設計する方法を学びました。

特に、以下の点を実践しました。

* `struct` を使用して関連するデータをまとめて管理する
* `enum` を使用してセンサーの状態を管理する
* 配列や構造体を関数へ渡して処理する
* ポインタを使用して関数から複数の値を返す
* 処理ごとに関数を分けてプログラムを整理する
* センサーデータを判定・集計し、結果を表示

 ## 今後の改善予定

今後は、以下の機能追加を検討しています。

* ファイルからのセンサーデータ読み込み
* 監視結果のログファイルへの保存
* タイムスタンプの追加
* 不正なセンサーデータに対するエラー処理
* ヘッダーファイルとソースファイルの分離
* リアルタイム監視を想定したセンサーデータのシミュレーション
