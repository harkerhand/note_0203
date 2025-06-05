import java.io.*;
import java.util.*;

class Student implements Serializable {
    private static final long serialVersionUID = 1L;
    private String name;
    private double score;

    public Student(String name, double score) {
        this.name = name;
        this.score = score;
    }

    @Override
    public String toString() {
        return "姓名: " + name + ", 分数: " + score;
    }

    public static void main(String[] args) {

        Student student = new Student("张三", 85.0);
        System.out.println(student.toString() + "类的实例化对象创建成功！");
    }
}

public class StudentDataManager {
    // RandName静态内部类，用于生成随机姓名
    static class RandName {
        private static final String[] FIRST_NAMES = { "张", "王", "李", "赵", "刘", "陈", "杨", "黄", "周", "吴",
                "徐", "孙", "马", "朱", "胡", "林", "郭", "何", "高", "罗" };
        private static final String[] SECOND_NAMES = { "伟", "芳", "娜", "秀英", "敏", "静", "强", "磊", "洋", "艳", "勇", "军", "杰",
                "娟", "涛", "明", "超", "霞", "平", "刚" };

        public static String generate() {
            Random random = new Random();
            String firstName = FIRST_NAMES[random.nextInt(FIRST_NAMES.length)];
            String secondName = SECOND_NAMES[random.nextInt(SECOND_NAMES.length)];
            return firstName + secondName;
        }
    }

    // 生成随机学号
    private static String randomId() {
        Random random = new Random();
        int middlePart = random.nextInt(9); // 0-8
        int endPart = random.nextInt(30) + 1; // 1-30
        return "711" + middlePart + String.format("%02d", endPart); // 格式化确保2位数字
    }

    // 生成随机分数
    private static double randomScore() {
        Random random = new Random();
        // 使用正态分布，均值为85
        // 标准差设为5，这样99.7%的值落在±15范围内(70-100)
        double score = random.nextGaussian() * 5 + 85;
        // 将值限制在0到100之间
        return Math.min(100, Math.max(0, score));
    }

    public static void main(String[] args) {
        HashMap<String, Student> studentMap = new HashMap<>();

        // 添加一些初始学生数据
        studentMap.put("71108501", new Student("张三", 80.0));
        studentMap.put("71108502", new Student("李四", 79.5));
        studentMap.put("71108503", new Student("王五", 91.0));
        studentMap.put("71108504", new Student("赵六", 60.0));
        studentMap.put("71108505", new Student("宋七", 18.6));

        // 生成更多随机学生数据
        for (int i = 0; i < 1000; i++) {
            String id = randomId();
            if (!studentMap.containsKey(id)) {
                String name = RandName.generate();
                double score = randomScore();
                studentMap.put(id, new Student(name, score));
            }
        }

        // 保存到文件
        String filename = "students.ser";
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(filename))) {
            oos.writeObject(studentMap);
            System.out.println("数据已保存到 " + filename);
        } catch (IOException e) {
            e.printStackTrace();
        }

        // 从文件中读取
        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(filename))) {
            HashMap<String, Student> loadedMap = (HashMap<String, Student>) ois.readObject();
            System.out.println("从文件读取的数据条数: " + loadedMap.size());
            System.out.println("示例输出前5条：");
            loadedMap.entrySet().stream().limit(5)
                    .forEach(entry -> System.out.println("学号: " + entry.getKey() + ", " + entry.getValue()));
            System.err.println("数据读取成功！");
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }
}