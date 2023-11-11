import cv2
import numpy as np
from paddle.inference import Config
from paddle.inference import PrecisionType
from paddle.inference import create_predictor
import yaml
import time
import serial as ser


def resize(img, target_size):
    """resize to target size"""
    if not isinstance(img, np.ndarray):
        raise TypeError('image type is not numpy.')
    im_shape = img.shape
    im_size_min = np.min(im_shape[0:2])
    im_size_max = np.max(im_shape[0:2])
    im_scale_x = float(target_size) / float(im_shape[1])
    im_scale_y = float(target_size) / float(im_shape[0])
    img = cv2.resize(img, None, None, fx=im_scale_x, fy=im_scale_y)
    return img

def normalize(img, mean, std):
    img = img / 255.0
    mean = np.array(mean)[np.newaxis, np.newaxis, :]
    std = np.array(std)[np.newaxis, np.newaxis, :]
    img -= mean
    img /= std
    return img

def preprocess(img, img_size):
    mean = [0.485, 0.456, 0.406]
    std = [0.229, 0.224, 0.225]
    img = resize(img, img_size)
    img = img[:, :, ::-1].astype('float32')  # bgr -> rgb
    img = normalize(img, mean, std)
    img = img.transpose((2, 0, 1))  # hwc -> chw
    return img[np.newaxis, :]

def predict_config(model_file, params_file):
    '''
    函数功能：初始化预测模型predictor
    函数输入：模型结构文件，模型参数文件
    函数输出：预测器predictor
    '''
    # 根据预测部署的实际情况，设置Config
    config = Config()
    # 读取模型文件
    config.set_prog_file(model_file)
    config.set_params_file(params_file)
    # Config默认是使用CPU预测，若要使用GPU预测，需要手动开启，设置运行的GPU卡号和分配的初始显存。
    config.enable_use_gpu(500, 0)
    # 可以设置开启IR优化、开启内存优化。
    config.switch_ir_optim()
    config.enable_memory_optim()
    config.enable_tensorrt_engine(workspace_size=1 << 30, precision_mode=PrecisionType.Float32,max_batch_size=1, min_subgraph_size=5, use_static=False, use_calib_mode=False)
    predictor = create_predictor(config)
    return predictor

def predict(predictor, img):
    
    '''
    函数功能：初始化预测模型predictor
    函数输入：模型结构文件，模型参数文件
    函数输出：预测器predictor
    '''
    input_names = predictor.get_input_names()
    for i, name in enumerate(input_names):
        input_tensor = predictor.get_input_handle(name)
        input_tensor.reshape(img[i].shape)
        input_tensor.copy_from_cpu(img[i].copy())
    # 执行Predictor
    predictor.run()
    # 获取输出
    results = []
    # 获取输出
    output_names = predictor.get_output_names()
    for i, name in enumerate(output_names):
        output_tensor = predictor.get_output_handle(name)
        output_data = output_tensor.copy_to_cpu()
        results.append(output_data)
    return results

def draw_bbox_image(frame, result, label_list, threshold=0.9):
    global rubish
    for res in result:
        cat_id, score, bbox = res[0], res[1], res[2:]
        if score < threshold:
    	    continue
        for i in bbox:
            int(i)
        xmin, ymin, xmax, ymax = bbox
        cv2.rectangle(frame, (int(xmin), int(ymin)), (int(xmax), int(ymax)), (255,0,255), 2)
     
        #print('category id is {}, bbox is {}'.format(cat_id, bbox))
        try:
            label_id = label_list[int(cat_id)]
            rubish =label_id
           # cv2.putText(图像, 文字, (x, y), 字体, 大小, (b, g, r), 宽度)
            cv2.putText(frame, label_id, (int(xmin), int(ymin-2)), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255,0,0), 2)
            cv2.putText(frame, str(round(score,2)), (int(xmin-35), int(ymin-2)), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0,255,0), 2)
        except KeyError:
            pass
def clear():
    global look_time
    global dc_num
    global yp_num
    global pp_num
    global nbz_num
    global bz_num
    global hlb_num
    global blb_num
    global td_num
    global cp_num
    global zk_num
    global els_num
    global ylg_num
    global slp_num
    dc_num = 0
    yp_num = 0
    pp_num = 0
    nbz_num = 0
    bz_num = 0
    hlb_num = 0
    blb_num = 0
    td_num = 0
    cp_num = 0
    zk_num = 0
    els_num = 0
    ylg_num = 0
    slp_num = 0

def sent_rubishi(rubbish):
    global str_ylg
    global str_Recylable
    global str_Other 
    global str_Harmful
    global str_KitchenWaste
    global str_OK
    global str_full 
    global se
    if rubbish == 'dc':
        se.write(str_Harmful.encode("GBK"))        
    elif rubbish == 'pp' or rubbish == 'yp' or rubbish == 'nbz' or rubbish == 'bz':
        se.write(str_Harmful.encode("GBK"))  
    elif rubbish == 'ylg':
        se.write(str_ylg.encode("GBK"))  
    elif rubbish == 'slp':
        se.write(str_Recylable.encode("GBK"))  
    elif rubbish == 'hlb'or rubbish == 'blb' or rubbish == 'td':
        se.write(str_KitchenWaste.encode("GBK"))  
    elif rubbish == 'cp'or rubbish == 'zk' or rubbish == 'els':
        se.write(str_Other.encode("GBK"))  

  
def wait_OK():
    global str_OK
    global str_full_1
    global str_full_2  
    str_anser=se.readline().decode("GB2312")
    while True:
        if str_anser==str_OK:
            print('OK')
            break
        elif str_anser==str_full_1 or str_anser==str_full_2:
            print('full')
            break
        str_anser=se.readline().decode("GB2312")

def print_rubishi(rubbish):
    global Harmful_num
    global Recyclable_num
    global Other_num
    global KitchenWaste_num
    global l1
    global l2
    global l3
    global l4
    global rubishi_sum
    rubishi_sum=rubishi_sum+1
    if rubbish == 'dc':
        Harmful_num = Harmful_num + 1
        print('第'+str(rubishi_sum)+'个：'+'有害垃圾'+'  '+'目前有害垃圾桶共有'+str(Harmful_num)+'件垃圾')
    elif rubbish == 'pp' or rubbish == 'yp' or rubbish == 'nbz' or rubbish == 'bz':
        Harmful_num = Harmful_num + 1
        print('第' + str(rubishi_sum) + '个：' + '有害垃圾' + '  ' + '目前有害垃圾桶共有' + str(Harmful_num) + '件垃圾')
    elif rubbish == 'ylg':
        Recyclable_num = Recyclable_num + 1
        print('第' + str(rubishi_sum) + '个：' + '可回收垃圾' + '  ' + '目前可回收垃圾桶共有' + str(Recyclable_num) + '件垃圾')
    elif rubbish == 'slp':
        Recyclable_num = Recyclable_num + 1
        print('第' + str(rubishi_sum) + '个：' + '可回收垃圾' + '  ' + '目前可回收垃圾桶共有' + str(Recyclable_num) + '件垃圾')
    elif rubbish == 'hlb'or rubbish == 'blb' or rubbish == 'td':
        KitchenWaste_num = KitchenWaste_num + 1
        print('第' + str(rubishi_sum) + '个：' + '厨余收垃圾' + '  ' + '目前厨余垃圾桶共有' + str(KitchenWaste_num) + '件垃圾')

    elif rubbish == 'cp'or rubbish == 'zk' or rubbish == 'els':
        Other_num = Other_num + 1
        print('第' + str(rubishi_sum) + '个：' + '其他收垃圾' + '  ' + '其他垃圾桶共有' + str(Other_num) + '件垃圾')

    

def average(rubish):
    global look_time
    global dc_num
    global yp_num
    global pp_num
    global nbz_num
    global bz_num
    global hlb_num
    global blb_num
    global td_num
    global cp_num
    global zk_num
    global els_num
    global ylg_num
    global slp_num
    if rubish=='dc':
        dc_num=dc_num+1
        if dc_num>=look_time:
            clear()
            sent_rubishi('')
            wait_OK()
            print_rubishi('dc')
    if rubish=='yp':
        yp_num=yp_num+1
        if yp_num>=look_time:
            clear()
            sent_rubishi('yp')
            wait_OK()
            print_rubishi('yp')
    if rubish == 'pp':
        pp_num = pp_num + 1
        if pp_num >= look_time:
            clear()
            sent_rubishi('pp')
            wait_OK()
            print_rubishi('pp')
    if rubish == 'nbz':
        nbz_num = nbz_num + 1
        if nbz_num>=look_time:
            clear()
            sent_rubishi('nbz')
            wait_OK()
            print_rubishi('nbz')
    if rubish == 'bz':
        bz_num = bz_num + 1
        if bz_num>=look_time:
            clear()
            sent_rubishi('bz')
            wait_OK()
            print_rubishi('bz')
    if rubish == 'td':
        td_num = td_num + 1
        if td_num>=look_time:
            clear()
            sent_rubishi('td')
            wait_OK()
            print_rubishi('td')
    if rubish == 'hlb':
        hlb_num = hlb_num + 1
        if hlb_num>=look_time:
            clear()
            sent_rubishi('hlb')
            wait_OK()
            print_rubishi('hlb')
    if rubish == 'blb':
        blb_num = blb_num + 1
        if blb_num>=look_time:
            clear()
            sent_rubishi('blb')
            wait_OK()
            print_rubishi('blb')
    if rubish == 'ylg':
        ylg_num = ylg_num + 1
        if ylg_num>=look_time:
            clear()
            sent_rubishi('ylg')
            wait_OK()
            print_rubishi('ylg')
    if rubish == 'slp':
        slp_num = slp_num + 1
        if slp_num>=look_time:
            clear()
            sent_rubishi('slp')
            wait_OK()
            print_rubishi('slp')
    if rubish == 'zk':
        zk_num = zk_num + 1
        if zk_num>=look_time:
            clear()
            sent_rubishi('zk')
            wait_OK()
            print_rubishi('zk')
    if rubish == 'cp':
        cp_num = cp_num + 1
        if cp_num>=look_time:
            clear()
            sent_rubishi('cp')
            wait_OK()
            print_rubishi('cp')
    if rubish == 'els':
        els_num = els_num + 1
        if hlb_num>=look_time:
            clear()
            sent_rubishi('els')
            wait_OK()
            print_rubishi('els')


infer_cfg = open('model/ppyolo_tiny_650e_coco_c/infer_cfg.yml')
data = infer_cfg.read()
yaml_reader = yaml.safe_load(data)
label_list = yaml_reader['label_list']
print(label_list)

# 配置模型参数
model_file = "model/ppyolo_tiny_650e_coco_c/model.pdmodel"
params_file = "model/ppyolo_tiny_650e_coco_c/model.pdiparams"
# 初始化预测模型
predictor = predict_config(model_file, params_file)

cap = cv2.VideoCapture(0)
#cap = cv2.VideoCapture("nvarguscamerasrc \                      !video/x-raw(memory:NVMM), width=640, height=480, format=NV12, framerate=30/1\
 #                      !nvvidconv flip-method=0 ! videoconvert ! video/x-raw, format=BGR ! #appsink")

# 图像尺寸相关参数初始化
ret, img = cap.read()
im_size = 320
scale_factor = np.array([im_size * 1. / img.shape[0], im_size * 1. / img.shape[1]]).reshape((1, 2)).astype(np.float32)
im_shape = np.array([im_size, im_size]).reshape((1, 2)).astype(np.float32)

#显示的初始化
look_time=100
rubish=''
dc_num=0
yp_num=0
pp_num=0
nbz_num=0
bz_num=0
hlb_num=0
blb_num=0
td_num=0
cp_num=0
zk_num=0
els_num=0
ylg_num=0
slp_num=0

Harmful_num=0
Recyclable_num=0
Other_num=0
KitchenWaste_num=0
rubishi_sum=0

#通信的初始化
str_ylg = "@ylg\r\n"
str_Recylable = "@Recyclable\r\n"
str_Other = "@Other\r\n"
str_Harmful = "@Harmful\r\n"
str_KitchenWaste = "@KitchenWaste\r\n"
str_OK= "OK"
str_full_1="full_1"
str_full_2="full_2"
se = ser.Serial("/dev/ttyTHS1", 9600, timeout=1)



while True:
    ret, frame = cap.read()
    # print(frame)
    # 预处理
    data = preprocess(frame, im_size)

    time_start = time.time()
    # 预测
    result = predict(predictor, [im_shape, data, scale_factor])
    #result = predict(predictor, [im_shape, data, scale_factor])
    #print(result)
    #print('Time Cost：{}'.format(time.time()-time_start) , "s")

    draw_bbox_image(frame, result[0], label_list, threshold=0.3)
    average(rubish)
    rubish='no'
    cv2.imshow("frame", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
