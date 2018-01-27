# 電腦輔助及防盜系統 - 程式內容及使用說明書  
### Computer Assistance and Anti-Theft System User Manual
#### Update time : 2018/1/27 
#### Author : Wade Lin

### Table of Contents  
[一、上傳程式碼到Arduino](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#%E4%B8%80%E4%B8%8A%E5%82%B3%E7%A8%8B%E5%BC%8F%E7%A2%BC%E5%88%B0arduino-)  
1. [上傳程式碼](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#1%E4%B8%8A%E5%82%B3%E7%A8%8B%E5%BC%8F%E7%A2%BC) 
2. [開啟監視視窗](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#2%E9%96%8B%E5%95%9F%E7%9B%A3%E8%A6%96%E8%A6%96%E7%AA%97) 
3. [顯示程式碼行數](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#3%E9%A1%AF%E7%A4%BA%E7%A8%8B%E5%BC%8F%E7%A2%BC%E8%A1%8C%E6%95%B8)   

[二、可更改之項目](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#%E4%BA%8C%E5%8F%AF%E6%9B%B4%E6%94%B9%E4%B9%8B%E9%A0%85%E7%9B%AE)  
1. [預設密碼](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#1%E9%A0%90%E8%A8%AD%E5%AF%86%E7%A2%BC)  
2. [密碼最大長度](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#2%E5%AF%86%E7%A2%BC%E6%9C%80%E5%A4%A7%E9%95%B7%E5%BA%A6-)   
3. [正式/測試模式](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#3%E6%AD%A3%E5%BC%8F%E6%B8%AC%E8%A9%A6%E6%A8%A1%E5%BC%8F-) 
4. [警訊傳輸值  ](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#4%E8%AD%A6%E8%A8%8A%E5%82%B3%E8%BC%B8%E5%80%BC-)  
5. [判斷開關機之持續時間](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#5%E5%88%A4%E6%96%B7%E9%96%8B%E9%97%9C%E6%A9%9F%E4%B9%8B%E6%8C%81%E7%BA%8C%E6%99%82%E9%96%93)   
6. [鎖/警報延遲](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#6%E4%B8%8A%E9%8E%96%E8%AD%A6%E5%A0%B1%E5%BB%B6%E9%81%B2)  
7. [MAC地址](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#7mac%E5%9C%B0%E5%9D%80)  

[三、功能按鍵](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#%E4%B8%89%E5%8A%9F%E8%83%BD%E6%8C%89%E9%8D%B5)  
1. [上鎖](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#1%E4%B8%8A%E9%8E%96)  
2. [解鎖](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#2%E8%A7%A3%E9%8E%96)  
3. [設定電腦運作電流/設定電腦睡眠電流](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#3%E8%A8%AD%E5%AE%9A%E9%9B%BB%E8%85%A6%E9%81%8B%E4%BD%9C%E9%9B%BB%E6%B5%81%E8%A8%AD%E5%AE%9A%E9%9B%BB%E8%85%A6%E7%9D%A1%E7%9C%A0%E9%9B%BB%E6%B5%81)  
4. [設定新密碼](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#4%E8%A8%AD%E5%AE%9A%E6%96%B0%E5%AF%86%E7%A2%BC)  

[四、實際測試](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#%E5%9B%9B%E5%AF%A6%E9%9A%9B%E6%B8%AC%E8%A9%A6)  
1. [開機(Setup)](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#1%E9%96%8B%E6%A9%9Fsetup)  
2. [斷電功能](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#2%E6%96%B7%E9%9B%BB%E5%8A%9F%E8%83%BD)  
3. [警鈴功能](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#3%E8%AD%A6%E9%88%B4%E5%8A%9F%E8%83%BD)  
4. [測試模式](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#4%E6%B8%AC%E8%A9%A6%E6%A8%A1%E5%BC%8F)  
5. [正式模式](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#5%E6%AD%A3%E5%BC%8F%E6%A8%A1%E5%BC%8F)  

[五、疑難排解](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#%E4%BA%94%E7%96%91%E9%9B%A3%E6%8E%92%E8%A7%A3)  
1. [連不上Ethernet擴展板](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#1%E9%80%A3%E4%B8%8D%E4%B8%8Aethernet%E6%93%B4%E5%B1%95%E6%9D%BF)
2. [伺服器IP位置](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#2%E4%BC%BA%E6%9C%8D%E5%99%A8ip%E4%BD%8D%E7%BD%AE-)
3. [如何安裝電腦電源到系統](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#3%E5%A6%82%E4%BD%95%E5%AE%89%E8%A3%9D%E9%9B%BB%E8%85%A6%E9%9B%BB%E6%BA%90%E5%88%B0%E7%B3%BB%E7%B5%B1)  

[六、還須更改及測試之部分](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#%E5%85%AD%E9%82%84%E9%A0%88%E6%9B%B4%E6%94%B9%E5%8F%8A%E6%B8%AC%E8%A9%A6%E4%B9%8B%E9%83%A8%E5%88%86)   
1. [網路訊息傳輸](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#1%E7%B6%B2%E8%B7%AF%E8%A8%8A%E6%81%AF%E5%82%B3%E8%BC%B8-)  
2. [其他細節](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#2%E5%85%B6%E4%BB%96%E7%B4%B0%E7%AF%80-)  

-----
## 一、上傳程式碼到Arduino   
首先，用USB傳輸線，連結Arduino開發板和電腦。  
從Tool(工具)裡，找到Board(開發板)選項；再從中找到「Arduino Uno」，並選取它。  

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/1-1.png" width="600" >  

從Tool(工具)裡，找到Port(連接阜/串口)選項。選取後面括弧有顯示Arduino Uno的Port。    

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/1-2.png" width="600" >  

	 【注意】串口前面的COM3中的數字3為電腦自動挑選的編號，每次連接或者每個開發板的數字都有可能不一樣。  

### 1.	上傳程式碼
首先，點擊左上角第一個有「打勾」之按鈕(Compile編譯)，此時，底下的狀態列會顯示「正在編譯」(Compiling sketch…)。

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/1-3.png" width="600" >  

	【注意】如果編譯有問題，底下的視窗欄會出現橘色的警告訊息，這時候就需要依照其所顯示的問題做修改。  

等進度條(黃色框)跑完後，再點擊左上角第二個有「箭頭」之按鈕(Upload上傳)。  

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/1-5.png" width="600" >  

此時，底下的狀態列也同樣會顯示「正在編譯」(Compiling sketch…)，但後面會接著顯示「上傳中」(Uploading…)。

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/1-4.png" width="600" >  
<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/1-7.png" width="600" >  

等上傳完成後，狀態列會顯示「上傳完成」(Done uploading…)，這樣就完成上傳程式的動作了。  

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/1-8.png" width="600" > 

	【注意】在上傳時，可以注意Arduino板上的指示LED燈(TX和RX)，當上傳時，LED燈會快速閃爍。   

### 2.	開啟監視視窗
從Tool(工具)裡，點擊Serial Monitor(序列埠輸出監控視窗)選項，就可以開啟訊息列。  

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/1-9.png" width="600" >

在程式中有許多資料輸出，可以在連接電腦的情況下監控Arduino運作的情況。但如果出現下面的情況：  

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/1-10.png" width="600" >

造成其錯誤的原因有  
1.USB未連接好 
2.未選取正確的Port(連接阜/串口)   

	【注意】若上述的動作都確認有做好，可以嘗試把USB拔掉再重插；若都不行，可換張Arduino板，因為可能是板子本身已經損壞。

### 3.	顯示程式碼行數
首先點擊工具列中的「檔案」(File)，找到「偏好設定」(Preferences)  

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/1-11.png" width="600" >

點擊後，找到「顯示程式碼行數」(Display line numbers)，並勾選起來。  

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/1-12.png" width="600" >   

## 二、	可更改之項目
### 1.	預設密碼
第九行在`#define`後面所定義的`CODE`值，為預設之系統密碼；可以隨意設定，但只僅能為羅馬數字0到9。

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/2-1.png" width="600" >

### 2.	密碼最大長度  
第十行在`#define`後面所定義的`CODE_MAX`值，為系統密碼之最大長度，可以隨意設定，但不建議設定超過9，系統可能會無法計算太長的數字密碼。

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/2-2.png" width="600" >

### 3.	正式/測試模式  
第11行的`TEST`為測試模式之開啟與否，若後面的數值為`0`則代表目前是「正式(正常)模式」；若為`1`則代表目前是「測試模式」。此兩者不同點在於觸動警鈴的方式和反應。

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/2-3.png" width="600" >

### 4.	警訊傳輸值  
第12和13行為定義之傳送參數數值：可依照需求作改寫，但後面的數值必須為字串，故必須要用`""`框起來。

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/2-4.png" width="600" >

### 5.	判斷開關機之持續時間 
當系統偵測到電腦處於睡眠狀態時，會開始計時連續持續時間，也就是下圖中的`SHUTDOWN_TIME`：  

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/2-5.png" width="600" >

例如上圖中的時間參數`SHUTDOWN_TIME`為`60`，代表電腦處於睡眠狀態後60秒，系統就會自動將電腦斷電關機。當系統將電腦關機後，會再度開始計時，並在`RESTART_TIME`後重新接上電源(通路)；時間參數`RESTART_TIME`為`10`，代表電腦處於斷電狀態後10秒，系統就會自動將電腦重新上電，但這時候電腦還是處於關機的狀態。  

	【注意】這裡的時間數值單位都是「秒」。

### 6.	上鎖/警報延遲
為了方便操作，在啟動上鎖功能和系統警報觸發時，會有時間延遲；延遲的時間(單位為秒)長度分別為`LOCK_DELAY`和`ALERT_DELAY`。

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/2-6.png" width="600" >

	【注意】這裡的時間數值單位都是「秒」。

### 7.	MAC地址
MAC地址為Ethernet擴展板本身的代號，總共有6組數字，前4組為固定值，後兩者可自由改寫。而通常只會改寫最後一個，例如：`OxFD`, `OxFE` ,`OxFF`…等。

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/2-7.png" width="600" >

	【注意】在定義之變數(例如：CODE_N)和後面的數值(例如：9)中間不能有任何符號，只能有空白鍵。

## 三、	功能按鍵
| | 按鍵`A`|按鍵`B`|按鍵`C`|按鍵`D`|按鍵`#`|按鍵`*`|
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|**一般情況**|系統上鎖|系統解鎖|設定電腦運作電流|設定電腦睡眠電流|設定新密碼|~無~|
|**解鎖程序**|返回鍵|清除鍵|取消|~無~|~無~|~無~|
|**設定密碼程序**|返回鍵|清除鍵|取消|~無~|~無~|輸入完成|

### 1.	上鎖
最右側英文字母`A`鍵為「系統上鎖」之功能。依據前面所設定之`LOCK_DELAY`時間，系統會在按下上鎖鍵後`LOCK_DELAY`秒後開啟防盜功能。

### 2.	解鎖
最右側英文字母`B`鍵為「系統解鎖」之功能。  
在按下解鎖鍵後，系統會進到解鎖程序中(此時防盜功能依然運作中)，這時原本的功能鍵之功能會變成「解鎖程序」之功能(可參見[上表](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#%E4%B8%89%E5%8A%9F%E8%83%BD%E6%8C%89%E9%8D%B5))。功能鍵之詳細功能說明：  
* `A`按鍵為「返回」-會消除最後輸入的數字
* `B`按鍵為「清除」-會消除全部輸入的數字
* `C`按鍵為「取消」-取消程序，並跳回原本的狀態 
同樣地，訊息欄也會顯示相關的訊息：

#### 【按鍵A】  
按下按鍵`A`後，會消除最後的數字，例如下圖：最後輸入數字3，所以被消除；並且系統會顯示到目前為止所輸入的密碼(除了消除的數字之外)，以方便系統問題修正。

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/4-1.png" width="600" >

#### 【按鍵B】  
按下按鍵`B`後，會消除全部的數字，例如下圖：  
按下`B`後，再重新打一次密碼，跳出密碼正確的訊息。  

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/4-2.png" width="600" >

#### 【按鍵C】  
按下按鍵`C`後，會取消解鎖模式，如下圖：

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/4-3.png" width="600" >

### 3.	設定電腦運作電流/設定電腦睡眠電流
最右側英文字母`C`和`D`鍵為「設定電腦運作/睡眠電流」之功能。在按下設定鍵後，系統會進到設定程序中(此時防盜系統依然運作中)，系統會自動紀錄當下的電流，並更新數據。  

	【注意】當系統重新啟動(Reset)後，電流參數會回復到預設值。
	
### 4.	設定新密碼
最底下符號`*`鍵為「系統解鎖」之功能。在按下設定密碼鍵後，系統會進到密碼設定程序中(此時防盜功能依然運作中)，首先要輸入舊的密碼，輸入正確後，系統會發出嗶嗶聲代表輸入正確(若輸入錯誤會發出5秒長畢聲)，然後再輸入新的密碼。  
新密碼的長度可自由設定，但不能超過最大密碼長度(請參見[密碼最大長度](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#2%E5%AF%86%E7%A2%BC%E6%9C%80%E5%A4%A7%E9%95%B7%E5%BA%A6-))，密碼輸入完成後，按下完成鍵，系統會發出嗶嗶聲，就代表設定完成。  

	【注意】當密碼設定達到最大密碼長度時，系統會強制並自動完成密碼設定，並發出嗶嗶聲。  
	
這時原本的功能鍵之功能會變成「設定密碼程序」之功能(可參見[上表](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#%E4%B8%89%E5%8A%9F%E8%83%BD%E6%8C%89%E9%8D%B5))。  
功能鍵之詳細功能說明為：   
* `A`按鍵為「返回」-會消除最後輸入的數字(與解鎖時相同)
* `B`按鍵為「清除」-會消除全部輸入的數字(與解鎖時相同)
* `C`按鍵為「取消」-取消程序，並跳回原本的狀態(與解鎖時相同)
* `#`按鍵為「完成輸入」-新密碼輸入完成後，按下完成鍵以完成新密碼設定。
##### 
	【注意】若正確按下功能鍵或數字鍵時，系統會發出一聲短的提示聲(短嗶嗶聲)；  
	而當按下不正確(沒有功能之按鍵)之按鍵時，系統會發出兩聲較長的提示聲(嗶嗶聲)。

## 四、	實際測試
### 1.	開機(Setup)
開機時若有連接Arduino到電腦，並[打開監視視窗](https://github.com/WadeLin3/Arduino/tree/master/Computer%20Alert%20System#2%E9%96%8B%E5%95%9F%E7%9B%A3%E8%A6%96%E8%A6%96%E7%AA%97)，接著就會看到監控視窗，裡面會顯示程式中所寫的訊息。第3行會顯示設定之密碼，然後進入設定網路擴充版程序。然而，如果沒有連接網路線或者網路線式無法連上網際網路時，會持續卡在這裡大約45秒至70秒，等設定時間超過後，系統會自動判斷無法連接網路，並繼續之後的程序(如下圖)：

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/5-1.png" width="600" >

	【注意】若有正常連接網路的話，其連接的速度會快很多。
	
	【注意】若沒有顯示出任何訊息，可重新插USB或者按Arduino板上的Reset鍵(紅色突起小按紐)。

等到訊息欄出現`「All setup complete!」`整個Setup程序才完成，此時系統也會發出嗶嗶聲和傳出開機/連接訊息。

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/5-2.png" width="600" >

正常的設定網路擴充版程序會如下圖：

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/5-3.png" width="600" >

### 2.	斷電功能
完成Setup後，系統會開始讀取電流和統計時間(Count)，此統計時間是用來記錄電源處於睡眠/開機時的持續時間。若電腦進入睡眠時間後，系統會偵測到電源電流振幅變小，並開始計時，當連續之持續時間到一定秒數(預設為60秒)後，系統會自動將電腦斷電。

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/5-4.png" width="600" >

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/5-5.png" width="600" >

	【注意】監控視窗左下角的「Autoroll」(紅框處)是指使否開啟自動下捲，若勾選，則視窗會一直往最新的訊息滑動。

下圖是當系統偵測到睡眠狀態持續60秒(預設)後的動作，當出現「Power Shutdown」就是指系統已經幫電腦進行自動斷電。

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/5-6.png" width="600" >

若系統判斷後將電腦斷電，會在10秒(預設)後再打電源打開；此時電腦還是處於關機的狀態。如果電腦開啟，系統會偵測到電流開始有大幅度的變化，也同樣地會開始計時持續時間，如果系統判斷到電腦已持續啟動超過60秒(預設)後，就會進入「電腦開啟」之狀態，此時系統就會又開始監控電腦狀態。

	【注意】以上的持續時間可作修改，欲修改數值，可參見之前的「可更改的項目-5」。

### 3.	警鈴功能
當系統啟動後，還是未上鎖的狀態(不會觸動警鈴)，必須按下`A`按鍵才會進入上鎖狀態，當按下`A`時，系統會發出嗶嗶聲和顯示在訊息欄，如下圖：
 
<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/5-7.png" width="600" >
 
此時，若觸動警鈴，系統就會啟動警報並發出訊息：
 
 <img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/5-8.png" width="600" >
 
	【注意】觸動警鈴的機制和警報如何啟動，會在之後的「測試模式」和「正式模式」做說明。

若要解鎖，則須按下`B`按鍵才會進入解鎖狀態，同樣地，當按下`B`時，系統會發出嗶嗶聲和顯示在訊息欄，如下圖。

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/5-9.png" width="600" >

此時，依序按下密碼，系統就會解鎖；每次按下按鍵都會發出嗶嗶聲，並顯示在訊息欄中。

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/5-10.png" width="600" >

解鎖成功後,系統也會發出嗶嗶聲。  

	【注意】若在解鎖模式時觸動警鈴，系統會依然啟動警鈴，並跳出解鎖模式。

### 4.	測試模式
測試模式為方便測試所設定的，若要使用測試模式，請將TEST參數設為1：
		
<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/5-11.png" width="600" >

在測試模式中，觸動警鈴的機制為「案下EndStop」，且觸發後的警鈴機制為長畢聲(持續0.5秒)。  
若要修改長畢聲次數或持續時間，可修改下圖中函數`Buzzer`括弧中的數據：

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/5-12.png" width="600" >

在括弧中，有兩個數據：第一個`1`代表警鈴響的次數；第二個`500`代表每次警鈴響的長度，單位為毫秒(500 = 0.5秒；1000 = 1秒)。

### 5.	正式模式
正式模式為正常情況之使用，在正式模式中，觸動警鈴的機制為「釋放EndStop」，且觸發後的警鈴機制為無限長畢聲，除非按下解鎖鍵並加以解鎖，否則警報會持續作用。  
若要使用正式模式，請將TEST參數設為0：
		
<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/5-13.png" width="600" >

## 五、	疑難排解
### 1.	連不上Ethernet擴展板
<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/6-1.png" width="600" > 

連不上網路擴張板(MAC地址無法使用)的原因可能為   
1. 未接上網路線  
2. 未能連上網際網路   
3. 網際網路為固定IP  
4. MAC地址錯誤(請參考先前之MAC說明)  

### 2.	伺服器IP位置  
若是要用連結網頁的方式進行訊息傳輸，則需要知道對方(網址)的IP地址，為了方便及系統穩定需求，網址的IP位置適合是「固定IP」，以免之後IP地址更變造成訊息傳輸錯誤。若只知道網址，則此網址的IP位置可由此方法得到：  

首先，在左下角找到「搜尋Windows」，輸入`cmd`並找到「命令提示字元」程式，點擊開啟。

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/6-2.png" width="600" >

開啟後，會看到一個黑底的視窗(如下圖)，在視窗中打上`ping`加上想要知道IP的網址名稱，這裡我用`google.com`作為範例：

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/6-3.png" width="600" >

輸入後按下Enter鍵，電腦就會傳送封包給server，此時就會顯示此網站的IP地址；此處可以看到`google.com`的IP位置為`172.217.160.78`。

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/6-4.png" width="600" >

	【注意】如果沒有出現成功接收傳送封包的訊息也沒有關係，只要有顯示出網址的IP位置就可以。
	
### 3.	如何安裝電腦電源到系統
由於此系統包含了偵測並控制電腦主機之電流狀況，所以安裝時必須將電腦主機之電源供應線連接到系統之「繼電器」和「電流感測器」上，相關的電路接法如下圖：

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/6-5.png" width="600" >

## 六、	還須更改及測試之部分
### 1.	網路訊息傳輸  
第17到19行的程式碼，原本是由於要使用`Maker.ifttt.com`進行的訊息傳輸之用，若要用其他方式進行訊息傳輸，必須更改此3行和其相關的方程式。  

<img src="https://github.com/WadeLin3/Arduino/blob/master/Computer%20Alert%20System/img/3-1.png" width="600" >

### 2.	其他細節  
由於相關的測試還沒有齊全，(例如：警鈴長度、功能按鍵、設備指示燈、BUG…等)，需要有專門的人員負責測試並改良相關的程式碼。  
