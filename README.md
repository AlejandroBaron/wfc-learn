# wfc-learn


Learning about the Wave Function Collapse algorithm.

## References

### How to run


First build the project with the following command:
```bash
make
```

Then
```bash
./wfc <input_file> <mode>
```

Mode can be one of the following:
- WEIGHTED: The algorithm will consider the weights of the tiles equal to the total count in the sample.
- CONSTANT: The algorithm will consider the weights of the tiles equal to 1.