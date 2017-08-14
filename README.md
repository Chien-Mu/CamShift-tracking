* 結合 Camera 即時測試 CAM Shift 演算法追蹤效果

* 主要是先 將影像轉換成 HSV 顏色域抽取 Hue channel，在以 calcbackproject 方式算出機率圖後，
  利用 CAM Shift 演算追蹤機率最密集的區域，並回傳 Rectangle(追蹤位置)
  
* 與 Mean Shift 演算法差在 CAM Shift 是 Mean Shift 的改良版，可以自動變化 kernel(Rectangle) 的大小

* 自動變化 kernel 大小的邏輯為
  一旦移位收斂，計算最佳擬合橢圓的方向
  再次，它使用新的縮放搜索窗口和以前的窗口位置的換算
  該過程一直持續到滿足要求的準確度
  
* 先按 Ctrl + S 就會出現截除視窗，讓使用者以滑鼠左鍵垃取 ROI，選取追蹤物體