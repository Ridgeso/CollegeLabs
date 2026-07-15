public enum Direction {
    LEFT (-1, 0),
    RIGHT(1, 0),
    UP(0, -1),
    DOWN(0, 1);

    Direction(int dirX, int dirY) {
        this.dirX = dirX;
        this.dirY = dirY;
    }

    public int getDirX() {
        return dirX;
    }

    public int getDirY() {
        return dirY;
    }

    final int dirX;
    final int dirY;
}
