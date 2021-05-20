# Features

* 實作 Camera 與 CamShift 結合，達到即時測試 Camshift algorithm 的即時效果

* 先將影像轉換成 HSV 顏色域後，抽取 Hue channel 以及以 calcbackproject 方式算出機率圖後，
利用 Camshift algorithm 追蹤機率最密集的區域，並回傳 Rectangle(追蹤位置)


# Screenshots

![image](https://github.com/Chien-Mu/CamShift-tracking/blob/master/resource/1_1.gif)
![image](https://github.com/Chien-Mu/CamShift-tracking/blob/master/resource/3.png)


# Usage

先按 Ctrl + S 就會出現截除視窗，讓使用者以滑鼠左鍵垃取 ROI，選取追蹤物體



***

# What is Camshift algorithm ?

the face image region has it's color histogram extracted, and the updated position is obtained by identifying a region close to the previous frame that matches the same color histogram. 
![image](https://github.com/Chien-Mu/CamShift-tracking/blob/master/resource/Camshift%20algorithm.png)


### Camshift vs MeanShift

* 與 Mean Shift 演算法差在 CAM Shift 是 Mean Shift 的改良版，可以自動變化 kernel(Rectangle) 的大小

* 自動變化 kernel 大小的邏輯為
  一旦移位收斂，計算最佳擬合橢圓的方向
  再次，它使用新的縮放搜索窗口和以前的窗口位置的換算
  該過程一直持續到滿足要求的準確度。
