* 結合 Camera 即時測試 MeanShift 演算法追蹤效果
* 主要是先 將影像轉換成 HSV 顏色域抽取 Hue channel，在以 calcbackproject 方式算出機率圖後，
  利用 MeanShift 演算追蹤機率最密集的區域，並回傳 Rectangle(追蹤位置)
* 先按 Ctrl + S 就會出現截除視窗，讓使用者以滑鼠左鍵垃取 ROI，選取追蹤物體